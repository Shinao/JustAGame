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
    sf::TcpSocket			_server;
  };

  // Private functions
  namespace
  {
    void		*listening_thread(void *)
    {
      while (_running)
      {
      }

      return (NULL);
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
      // if (_server.bind(port) != sf::Socket::Done)
	// return (false);
      // _listener.add(_server);
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
