#include <map>
#include <pthread.h>
#include <iostream>
#include "Network.hh"

namespace		Network
{
  // Private members
  namespace
  {
    struct 		RequestInfo
    {
      RequestID		id;
      Client		*client;
      bool		reliable;
      sf::Packet	packet;
    };

    // Threading the network
    sf::Thread				*_thread;
    sf::Mutex				_mutex;
    bool				_running;

    std::vector<Client *>		_clients;
    std::map<RequestID, CallbackRequest>	_requests_callback;

    // Socket
    std::vector<RequestInfo *>		_requests_pending;
    std::vector<Client *>		_clients_disconnected;
    bool				_is_server;
    sf::SocketSelector			_listener;
    sf::UdpSocket			_udp_socket;

    //// Reliability
    Sequence				_sequence;
    // Reliable packets waiting for acknowledgement
    std::map<Sequence, ProtocoledPacket *>	_waiting_packets;

    // Server sided
    sf::TcpListener			_server;

    void				clientDisconnected(Client *client);
    void				addPendingConnection();
    bool				checkHeader(RequestInfo &info);
    void				checkAcknowledgement(RequestInfo &info);
    void				checkUdp();
    void				checkTcp(Client *client);
    void				addPacket(RequestInfo *info);
  };

  // Private functions
  namespace
  {
    void		listening_thread()
    {
      while (_running)
      {
	_listener.wait();
	std::cout << "Listener unblocked" << std::endl;

	_mutex.lock();

	// Check server
	if (_is_server && _listener.isReady(_server))
	  addPendingConnection();
	// Check UDP
	if (_listener.isReady(_udp_socket))
	  checkUdp();
	// Check client
	for (auto client : _clients)
	  if (_listener.isReady(client->getSocket()))
	    checkTcp(client);

	_mutex.unlock();
      }
    }

    bool		checkHeader(RequestInfo &info)
    {
      ProtocolInfo	protocol = 0;
      info.packet >> protocol;

      if ((protocol & Network::PROTOCOL_MAGIC) != Network::PROTOCOL_MAGIC)
	return (false);

      info.reliable = (protocol & 0x1);
      return (true);
    }

    void		checkUdp()
    {
      sf::IpAddress	sender;
      unsigned short	port;
      RequestInfo	*info = new RequestInfo();

      // Dropping request
      if (_udp_socket.receive(info->packet, sender, port) != sf::Socket::Done ||
	  !checkHeader(*info))
      {
	delete info;
	return ;
      }

      // Get client
      Client		*client = NULL;
      for (auto search : _clients)
	if (search->getIp() == sender)
	  client = search;

      // UDP Unconnected
      if (client != NULL)
      {
	client = new Client();
	client->setIp(sender);
      }

      info->client = client;

      // Manage acknowledgement
      if (client != NULL)
	checkAcknowledgement(*info);

      addPacket(info);
    }

    void		checkAcknowledgement(RequestInfo &info)
    {
      Sequence		remote_sequence;
      Sequence		ack;
      AcknowledgeField	field;
      AcknowledgeField	diff;

      info.packet >> remote_sequence >> ack >> field;
      info.client->updateSequence(remote_sequence);

      // Remove waiting packet if in ackfield or out of bounds
      for (auto it = _waiting_packets.begin(); it != _waiting_packets.end(); ++it)
      {
	// If ack is inferior to our sequence - just wait next turn baby
	if (isSequenceMoreRecent(ack, it->second->getSequence()))
	  continue ;

	diff = getSequenceDifference(ack, it->second->getSequence());

	// Found it - Drop it
	if (field & (0x1 << (ACKFIELD_SIZE - diff)))
	{
	  std::cout << "OUR Packet [" << it->second->getSequence() << "]" << " acked" << std::endl;
	  _waiting_packets.erase((it--)->second->getSequence());
	}
      }

      // Still have packet ? Resend them !
      for (auto it : _waiting_packets)
	send(it.second);
    }

    void		addPacket(RequestInfo *info)
    {
      // Retrieve RequestID
      info->packet >> info->id;
      std::cout << "Request - ID [" << info->id << "]" << std::endl;

      // Add request
      _requests_pending.push_back(info);
    }

    void		checkTcp(Client *client)
    {
      RequestInfo	*info = new RequestInfo();

      // Check if client disconnected
      sf::Socket::Status status = client->getSocket().receive(info->packet);

      info->client = client;
      if (status != sf::Socket::Done || !checkHeader(*info))
      {
	info->id = Request::Disconnexion;
	_requests_pending.push_back(info);
	_clients_disconnected.push_back(client);
      }
      else
      {
	checkAcknowledgement(*info);
	addPacket(info);
      }
    }

    void		addPendingConnection()
    {
      std::cout << "New client" << std::endl;

      sf::TcpSocket	*socket = new sf::TcpSocket();
      if (_server.accept(*socket) == sf::Socket::Done)
      {
	Client	*client = new Client();
	client->setSocket(socket);

	// New client request
	RequestInfo	*info = new RequestInfo();
	info->id = Request::Connexion;
	info->client = client;
	_requests_pending.push_back(info);
      }
    }
  };

  bool			init(int port, int is_server)
  {
    _is_server = is_server;
    _running = true;

    // Listen
    if (_udp_socket.bind(port) != sf::Socket::Done)
      return (false);
    _listener.add(_udp_socket);

    if (_is_server)
    {
      if (_server.listen(port) != sf::Socket::Done)
	return (false);
      _listener.add(_server);
    }

    // Launch listening thread
    _thread = new sf::Thread(&listening_thread);
    _thread->launch();

    return (true);
  }

  void			clear()
  {
    // Waiting for thread
    _running = false;
    // Force listener to unwait
    _udp_socket.unbind();
    // Waiting because we are gentle
    _thread->wait();
    delete _thread;

    // Free ressources
    for (auto client : _clients)
      delete client;
  }

  // Call callbacks for all requests received
  void			update()
  {
    // Don't do all the work, there is probably nothing
    if (_requests_pending.size() == 0)
      return ;

    // It's safe baby
    _mutex.lock();

    // Check all requests
    for (auto req_info : _requests_pending)
    {
      // Get callback and call it
      auto it = _requests_callback.find(req_info->id);
      if (it != _requests_callback.end())
      {
	std::cout << "Request found with callback" << std::endl;
	it->second(req_info->client, req_info->packet);
      }

      delete req_info;
    }
    _requests_pending.clear();

    // Check disconnected clients
    for (auto client : _clients_disconnected)
    {
      for(std::vector<Client *>::iterator search = _clients.begin(); search != _clients.end(); ++search)
	if (*search == client)
	{
	  _clients.erase(search);
	  break ;
	}

      delete client;
    }
    _clients_disconnected.clear();

    _mutex.unlock();
  }

  // Used to identify servers over the network
  void				send(ProtocoledPacket *packet, const sf::IpAddress &ip, unsigned short port)
  {
    _udp_socket.send(*packet, ip, port);

    // Unconnected - delete it
    delete packet;
  }

  void				send(ProtocoledPacket *packet)
  {
    packet->getClient()->getSocket().send(*packet);

    // Not reliable - Discard it
    if (!packet->isReliable())
    {
      delete packet;
      return ;
    }

    _mutex.lock();
    _waiting_packets[packet->getSequence()] = packet;
    _mutex.unlock();
  }

  void			addRequest(RequestID id, const CallbackRequest &cb)
  {
    _requests_callback[id] = cb;
  }

  AcknowledgeField	getSequenceDifference(Sequence seq1, Sequence seq2)
  {
    // Looped
    if (seq1 - seq2 > Network::MAX_SEQUENCE / 2)
    {
      AcknowledgeField max = std::max(seq1, seq2);
      AcknowledgeField min = std::min(seq1, seq2);

      min += Network::MAX_SEQUENCE - max;
      max = 0;
    }

    return ((seq1 - seq2) * -1);
  }


  bool			isSequenceMoreRecent(Sequence sequence, Sequence check_sequence)
  {
    return ((check_sequence > sequence) && (check_sequence - sequence <= Network::MAX_SEQUENCE / 2)) ||
      ((sequence > check_sequence) && (sequence - check_sequence > Network::MAX_SEQUENCE / 2));
  }
};
