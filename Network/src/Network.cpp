#include <map>
#include <list>
#include <iostream>
#include "Network.hh"

const char * RequestString[] = { "Ping", "Allo", "Connexion", "Disconnexion", "Update",
"UDPEstablishment", "UDPEstablished", "Test"};

namespace		Network
{
  //
  // Private members
  //
  namespace
  {
    // Threading the network
    sf::Thread				*_thread;
    sf::Mutex				_mutex;
    bool				_running;

    // Client
    std::vector<Client *>		_clients;
    // Client waiting for UDP Establishment
    std::list<Client *>			_waiting_clients;
    std::map<RequestID, CallbackRequest>	_requests_callback;

    // Socket
    std::vector<ProtocoledPacket *>	_requests_pending;
    std::vector<ProtocoledPacket *>	_requests_pending_later;
    std::vector<Client *>		_clients_disconnected;
    bool				_is_server;
    sf::SocketSelector			_listener;
    sf::UdpSocket			_udp_socket;

    // Reliable packets waiting for acknowledgement
    std::map<Sequence, ProtocoledPacket *>	_waiting_packets;

    //
    // Server sided
    //
    sf::TcpListener			_server;
    // Utility
    sf::Clock				_update_clock;


    void				clientDisconnected(Client *client);
    void				addPendingConnection();
    bool				checkHeader(ProtocoledPacket &info);
    void				checkAcknowledgement(ProtocoledPacket &info);
    void				checkUdp();
    void				checkTcp(Client *client);
    void				addRequest(ProtocoledPacket *info);
    void				sendUpdate();
    void				sendUdpClient(ProtocoledPacket *packet);
    void				connecting_thread(Client *client);

    // Request Callback
    void				UDPEstablished(ProtocoledPacket &packet);
    void				UDPEstablishment(ProtocoledPacket &packet);
  };


  //
  // Private functions
  //
  namespace
  {
    void		connecting_thread(Client *client)
    {
      sf::TcpSocket	*socket = new sf::TcpSocket();

      // Could not connect
      if (socket->connect(client->getIp(), client->getPort(), sf::seconds(2)) != sf::Socket::Done)
      {
	ProtocoledPacket	*packet = new ProtocoledPacket();

	packet->setClient(client);
	if (_requests_callback[Request::Disconnexion])
	  _requests_callback[Request::Disconnexion](*packet);

	delete packet;
	delete socket;
      }

      // TCP Connected - Waiting for UDP Established to letting know the user
      client->setSocket(socket);
      // Safety
      sf::Lock lock(_mutex);
      _listener.add(*socket);
      _clients.push_back(client);
    }

    void		listening_thread()
    {
      while (_running)
      {
	// Server update to client - Waiting Clients / Ping and other stuff
	if (_is_server)
	  sendUpdate();

	if (!_listener.wait(sf::milliseconds(UPDATE_INTERVAL)))
	  continue ;

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
      }
    }

    // Send ping to client if server and other stuff
    void		sendUpdate()
    {
      // Wait for your turn !
      if (_update_clock.getElapsedTime().asMilliseconds() < UPDATE_INTERVAL)
	return ;

      _mutex.lock();

      // Still in the waiting list ? Resend !
      for (auto client : _waiting_clients)
      {
	ProtocoledPacket *packet = new ProtocoledPacket(client, Request::UDPEstablishment, Network::TCP);
	*packet << client->getId();
	send(packet);
      }

      // Create Update Packet
      sf::Packet info_packet;
      // Number of client
      info_packet << _clients.size();
      for (auto client : _clients)
	info_packet << client->getId() << client->getPing();

      // For all client send unreliable packet
      for (auto client : _clients)
      {
	ProtocoledPacket *packet = new ProtocoledPacket(client, Request::Update, Network::Unreliable);
	packet->append(info_packet.getData(), info_packet.getDataSize());
	send(packet);
      }

      _mutex.unlock();

      _update_clock.restart();
    }

    bool		checkHeader(ProtocoledPacket &info)
    {
      ProtocolInfo	protocol = 0;
      info >> protocol;

      if ((protocol & Network::PROTOCOL_MAGIC) != Network::PROTOCOL_MAGIC)
	return (false);

      // Reliable - Useful to update remote sequence in UDP
      // Set Reliability
      info.setReliability((protocol & 0x1) ? Network::UDPReliable : Network::Unreliable);

      return (true);
    }

    void		checkUdp()
    {
      sf::IpAddress	sender;
      unsigned short	port;
      ProtocoledPacket	*info = new ProtocoledPacket();

      // Dropping request
      if (_udp_socket.receive(*info, sender, port) != sf::Socket::Done ||
	  !checkHeader(*info))
      {
	delete info;
	return ;
      }

      _mutex.lock();

      std::cout << "[CheckUdp] UDP Request" << std::endl;

      // Get client
      Client		*client = NULL;
      for (auto search : _clients)
	if (search->getIp() == sender && search->getPort() == port)
	  client = search;

      // UDP Unconnected
      if (client == NULL)
      {
	client = new Client();
	client->setIp(sender);
	client->setPort(port);
	info->setReliability(Network::Unconnected);
	info->setClient(client);
      }
      // Manage acknowledgement
      else
      {
	// Update sequence if necessary
	if (info->hasAcknowledgment())
	{
	  Sequence		remote_sequence;
	  *info >> remote_sequence;
	  info->getClient()->updateSequence(remote_sequence);
	}

	checkAcknowledgement(*info);
      }

      addRequest(info);

      _mutex.unlock();
    }

    void		checkAcknowledgement(ProtocoledPacket &info)
    {
      Sequence		ack;
      AcknowledgeField	field;
      AcknowledgeField	diff;

      info >> ack >> field;

      // Remove waiting packet if in ackfield or out of bounds
      for (auto it = _waiting_packets.begin(); it != _waiting_packets.end(); ++it)
      {
	// If ack is inferior to our sequence - just wait next turn baby
	if (isSequenceMoreRecent(ack, it->second->getSequence()))
	  continue ;

	diff = getSequenceDifference(ack, it->second->getSequence());

	// If our packet is out of ackfield - Generate a new Sequence to be on top
	if (diff > ACKFIELD_SIZE)
	{
	  it->second->generateSequence();
	  continue ;
	}

	// Found it - Drop it
	if (field & (0x1 << (ACKFIELD_SIZE - diff)))
	{
	  std::cout << "[CheckAcknowledgment] Our Packet [" << it->second->getSequence() << "]" << " acked" << std::endl;

	  // It's an acknowledgment packet - Update ping
	  info.getClient()->addPing(it->second->getElapsedTime());

	  _waiting_packets.erase((it--)->second->getSequence());
	}
      }

      // Still have packet ? Resend them ! (Avoiding doublon by calling directly sendUdpClient
      for (auto it : _waiting_packets)
	sendUdpClient(it.second);
    }

    void		addRequest(ProtocoledPacket *info)
    {
      // Retrieve RequestID
      RequestID id;
      *info >> id;
      info->setRequestID(id);
      std::cout << "[addRequest] ID [" << RequestString[info->getRequestID()] << "]" << std::endl;

      // Add request
      _requests_pending.push_back(info);
    }

    void		checkTcp(Client *client)
    {
      _mutex.lock();

      ProtocoledPacket	*info = new ProtocoledPacket();
      info->setClient(client);

      sf::Socket::Status status = client->getSocket().receive(*info);

      // Check if client disconnected
      if (status != sf::Socket::Done || !checkHeader(*info))
      {
	_listener.remove(client->getSocket());
	info->setRequestID(Request::Disconnexion);
	_requests_pending.push_back(info);
	_clients_disconnected.push_back(client);
      }
      // Good Request
      else
      {
	checkAcknowledgement(*info);
	addRequest(info);
      }

      _mutex.unlock();
    }

    void		addPendingConnection()
    {
      _mutex.lock();

      sf::TcpSocket	*socket = new sf::TcpSocket();
      if (_server.accept(*socket) == sf::Socket::Done)
      {
	std::cout << "[addPendingConnection] New client" << std::endl;

	// Add to waiting list for UDP
	Client	*client = new Client();
	client->setSocket(socket);
	_waiting_clients.push_back(client);

	// Before new client request - get a UDP Request to set the port
	ProtocoledPacket *packet = new ProtocoledPacket(client, Request::UDPEstablishment, Network::TCP);
	*packet << client->getId();
	send(packet);
      }

      _mutex.unlock();
    }

    // Main Thread - Request Callback - TCP
    // Server wants to get a UDP Request for port UDP
    void				UDPEstablishment(ProtocoledPacket &packet)
    {
      // Safety - Only client get this request
      if (_is_server)
	return ;

      ProtocoledPacket	*rsp = new ProtocoledPacket(NULL, Request::UDPEstablished, Network::Unconnected);
      ClientID	id;
      packet >> id;

      std::cout << "[UDPEstablishment] Establishment -> Send UDP [" << id << "]"  << std::endl;

      *rsp << id;
      send(rsp, packet.getClient()->getIp(), packet.getClient()->getPort());
    }

    // Main Thread - Request Callback - UDP Server / TCP Client
    // Server: Complete the client with the port for the UDP for the server
    // Client: Callback client
    void				UDPEstablished(ProtocoledPacket &packet)
    {
      std::cout << "[UDPEstablished]" << std::endl;

      // Server completed - Our turn
      if (!_is_server)
      {
	std::cout << "[UDPEstablished] Client" << std::endl;
	// New client request
	ProtocoledPacket	*info = new ProtocoledPacket();
	info->setRequestID(Request::Connexion);
	info->setClient(packet.getClient());
	_requests_pending_later.push_back(info);

	return ;
      }

      // Server : UDP Configuration - Client complete
      Client	*client = NULL;
      ClientID	id;
      packet >> id;

      std::cout << "[UDPEstablished] New client [" << id << "]" << std::endl;

      // Get the client from the id and ip in the waiting list
      for (auto search : _waiting_clients)
	if (search->getId() == id && search->getIp() == packet.getClient()->getIp())
	  client = search;

      // Not found - Abort
      if (client == NULL)
	return ;

      client->setPort(packet.getClient()->getPort());
      // Add client
      _waiting_clients.remove(client);
      _clients.push_back(client);

      // Letting now the client we are ready
      std::cout << "[UDPEstablished] Sending UDP Established to client TCP" << std::endl;
      ProtocoledPacket *ready = new ProtocoledPacket(client, Request::UDPEstablished, Network::TCP);
      send(ready);

      // New client request
      ProtocoledPacket	*info = new ProtocoledPacket();
      info->setRequestID(Request::Connexion);
      info->setClient(client);
      _requests_pending_later.push_back(info);
    }

    void				sendUdpClient(ProtocoledPacket *packet)
    {
      _udp_socket.send(*packet, packet->getClient()->getIp(), packet->getClient()->getPort());
    }
  };



  //
  // Public
  //
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

    // Listeners
    using namespace std::placeholders;
    addRequest(Request::UDPEstablishment, std::bind(&UDPEstablishment, _1));
    addRequest(Request::UDPEstablished, std::bind(&UDPEstablished, _1));

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
    sf::Lock lock(_mutex);

    // Check all requests
    for (auto req_info : _requests_pending)
    {
      std::cout << "Request callback [" << RequestString[req_info->getRequestID()] << "]" << std::endl;

      // Get callback and call it
      auto it = _requests_callback.find(req_info->getRequestID());
      if (it != _requests_callback.end())
      {
	it->second(*req_info);
      }
      else
	std::cout << "Not found" << std::endl;

      // Delete client if unconnected Request
      if (req_info->getReliability() == Network::Unconnected)
	delete req_info->getClient();

      delete req_info;
    }
    _requests_pending.clear();

    // If we added request when we were into the request callback
    if (_requests_pending_later.size())
    {
      for (auto req_later : _requests_pending_later)
	_requests_pending.push_back(req_later);
      _requests_pending_later.clear();
    }


    // Check disconnected clients
    for (auto client : _clients_disconnected)
    {
      std::cout << "[Update] Client [" << client->getId() << "] disconnected" << std::endl;
      for(std::vector<Client *>::iterator search = _clients.begin(); search != _clients.end(); ++search)
	if (*search == client)
	{
	  _clients.erase(search);
	  break ;
	}

      delete client;
    }
    _clients_disconnected.clear();
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
    if (packet->getReliability() == Network::TCP)
      packet->getClient()->getSocket().send(*packet);
    else
      sendUdpClient(packet);

    // No acknowledgment wanted - Discard it
    if (!packet->hasAcknowledgment())
    {
      delete packet;
      return ;
    }

    // Drop other packet with same reliability and RequestID
    if (packet->getReliability() == Network::UDPVariable)
    {
      for (std::map<Sequence, ProtocoledPacket *>::iterator it = _waiting_packets.begin();
	  it != _waiting_packets.end(); ++it)
	{
	  if (it->second->getRequestID() == packet->getRequestID() &&
	      it->second->getReliability() == Network::UDPVariable)
	  {
	    delete it->second;
	    _waiting_packets.erase(it);
	  }
	}
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

  void			connect(Client *client)
  {
    // using namespace std::placeholders;
    sf::Thread	thread(std::bind(connecting_thread, client));
    thread.launch();
  }
};
