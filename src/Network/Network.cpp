#include <map>
#include <pthread.h>
#include <iostream>
#include "Network/Network.hh"

namespace		Network
{
  // Private members
  namespace
  {
    // Threading the network
    pthread_t				_thread;
    pthread_mutex_t			_mutex;
    bool				_running;

    std::vector<Client *>		_clients;
    std::map<RequestID, Callback>	_requests;

    // Socket
    bool				_is_server;
    sf::SocketSelector			_listener;
    sf::UdpSocket			_udp_socket;
    // Only used if server
    sf::TcpListener			_server;

    void				addPendingConnection();
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
	// Check client
	for (auto client : _clients)
	  if (_listener.isReady(client->getSocket()))
	  {
	  }
      }

      return (NULL);
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
    pthread_create(&_thread, NULL, listening_thread, NULL);

    return (true);
  }

  void			clear()
  {
    // Waiting for thread
    _running = false;
    void	*ptr;
    pthread_join(_thread, &ptr);

    // Free ressources
    for (auto client : _clients)
      delete client;
  }

  // Call callbacks for all requests received
  void			update()
  {
  }
};
