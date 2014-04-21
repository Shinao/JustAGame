#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <pthread.h>

class Test
{
  private:
    int nb;
    pthread_t	_thread;

  public:
    Test() { 
      nb = -10;
      pthread_create(&_thread, NULL, &Test::thread_function, this);
    }

    static void* thread_function(void*myclass) {
      Test *test = (Test*) myclass;
      test->nb = 0;
    return (NULL); }

    void inc() { ++nb; }
    void dec() { --nb; }
    int get() { return (nb); }
};

void	server();
void	client();

int	main(int ac, char **av)
{
  std::cout << "basic server" << std::endl;
  // Test test;
  // sf::sleep(sf::seconds(1));
  // std::cout << test.get() << std::endl;

  if (ac > 1)
    server();
  else
    client();
}

void	server()
{
  sf::UdpSocket _socket;
  sf::UdpSocket _socket2;

  if (_socket.bind(25052) != sf::Socket::Done)
  {
    std::cout << "can't bind" << std::endl;
    return ;
  }
  sf::SocketSelector _listener;
  _listener.add(_socket);
  _listener.add(_socket2);

  char buffer[1024];
  std::size_t received = 0;
  sf::IpAddress sender;
  unsigned short port;

  sf::Packet packet;
  packet << (uint16_t) 0 << (uint16_t) 1;

  while (1)
  {
    _listener.wait();
    if (_listener.isReady(_socket))
    {
      _socket.receive(buffer, sizeof(buffer), received, sender, port);
      _socket.send(packet, sender, port);
    }
  }
}

void 	client()
{
  sf::UdpSocket _socket;

  if (_socket.bind(52025) != sf::Socket::Done)
  {
    std::cout << "can't bind" << std::endl;
    return ;
  }

  _socket.send("ping", 5, sf::IpAddress::Broadcast, 25052);
}
