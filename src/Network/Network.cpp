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
    std::map<RequestID, CallbackNet>	_requests_callback;

    // Socket
    std::vector<RequestInfo *>		_requests_pending;
    bool				_is_server;
    sf::SocketSelector			_listener;
    sf::UdpSocket			_udp_socket;

    // Server sided
    sf::TcpListener			_server;

    // Client sided

    void				addPendingConnection();
    void				checkUdp();
    void				checkClient(Client *client);
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

	// Check server
	if (_is_server && _listener.isReady(_server))
	  addPendingConnection();
	// Check UDP
	if (_listener.isReady(_udp_socket))
	  checkUdp();
	// Check client
	for (auto client : _clients)
	  if (_listener.isReady(client->getSocket()))
	    checkClient(client);
      }

      return (NULL);
    }

    void		checkUdp()
    {
      RequestInfo	*info = new RequestInfo();
      sf::IpAddress	sender;
      unsigned short	port;

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
	for (auto cli : _clients)
	  if (cli->getId() == client_id)
	    client = cli;

      info->client = client;
      info->packet >> info->id;
      std::cout << "UDP Request - ID [" << info->id << "]" << std::endl;

      // Add request
      pthread_mutex_lock(&_mutex);
      _requests_pending.push_back(info);
      pthread_mutex_unlock(&_mutex);
    }

    void		checkClient(Client *client)
    {
      std::cout << "Tcp request" << std::endl;
    }

    void		addPendingConnection()
    {
      std::cout << "New client" << std::endl;
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

      std::cout << "get callback" << std::endl;
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

    pthread_mutex_unlock(&_mutex);
    // std::cout << "unlock" << std::endl;
  }

  // Used to identify servers over the network
  sf::Socket::Status		send(sf::Packet &packet, const sf::IpAddress &ip, unsigned short port)
  {
    return (_udp_socket.send(packet, ip, port));
  }

  sf::Socket::Status		send(sf::Packet &packet, Client *client)
  {
    return (sf::Socket::Done);
  }

  void			addRequest(RequestID id, const CallbackNet &cb)
  {
    _requests_callback[id] = cb;
  }
};
