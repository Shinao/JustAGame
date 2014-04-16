#include <map>
#include <pthread.h>
#include <iostream>
#include "Network/Network.hh"

namespace		Network
{
  // Private members
  namespace
  {
    struct 		RequestInfo
    {
      RequestID		id;
      Client		*client;
      sf::Packet	packet;
    };

    // Threading the network
    pthread_t				_thread;
    pthread_mutex_t			_mutex;
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
    void				checkUdp();
    void				checkTcp(Client *client);
  };

  // Private functions
  namespace
  {
    void		*listening_thread(void *)
    {
      while (_running)
      {
	_listener.wait();
	std::cout << "Listener unblocked" << std::endl;

	pthread_mutex_lock(&_mutex);

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

	pthread_mutex_unlock(&_mutex);
      }

      return (NULL);
    }

    void		checkUdp()
    {
      sf::IpAddress	sender;
      unsigned short	port;
      RequestInfo	*info = new RequestInfo();

      // Dropping request
      if (_udp_socket.receive(info->packet, sender, port) != sf::Socket::Done)
      {
	delete info;
	return ;
      }

      // Get client
      Client		*client;
      ClientID client_id;
      info->packet >> client_id;
      if (client_id == 0)
      {
	client = new Client();
	client->setIp(sender);
      }
      else
	for (auto search : _clients)
	  if (search->getId() == client_id)
	    client = search;

      info->client = client;
      info->packet >> info->id;
      std::cout << "UDP Request - ID [" << info->id << "]" << std::endl;

      // Add request
      _requests_pending.push_back(info);
    }

    void		checkTcp(Client *client)
    {
      RequestInfo	*info = new RequestInfo();

      // Check if client disconnected
      sf::Socket::Status status = client->getSocket().receive(info->packet);
      
      info->client = client;
      if (status != sf::Socket::Done)
      {
	info->id = Request::Disconnexion;
	_clients_disconnected.push_back(client);
      }
      else
      {
	info->packet >> info->id;
	std::cout << "TCP Request - ID [" << info->id << "]" << std::endl;
      }

      // Add request
      _requests_pending.push_back(info);
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
    pthread_mutex_init(&_mutex, NULL);
    pthread_create(&_thread, NULL, listening_thread, NULL);

    return (true);
  }

  void			clear()
  {
    // Waiting for thread
    _running = false;
    // Force listener to unwait
    _udp_socket.unbind();
    // Useless return ptr
    void	*ptr;
    pthread_join(_thread, &ptr);

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
    pthread_mutex_lock(&_mutex);

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

    pthread_mutex_unlock(&_mutex);
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
  }

  void			addRequest(RequestID id, const CallbackRequest &cb)
  {
    _requests_callback[id] = cb;
  }
};
