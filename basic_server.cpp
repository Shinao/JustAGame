#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>

void	server();
void	client();

int	main(int ac, char **av)
{
  if (ac > 1)
    server();
  else
    client();
}

void	server()
{
  sf::UdpSocket _socket;

  if (_socket.bind(25052) != sf::Socket::Done)
  {
    std::cout << "can't bind" << std::endl;
    return ;
  }
  sf::SocketSelector _listener;
  _listener.add(_socket);

  char buffer[1024];
  std::size_t received = 0;
  sf::IpAddress sender;
  unsigned short port;

  while (1)
  {
    if (_listener.isReady(_socket))
    {
      _socket.receive(buffer, sizeof(buffer), received, sender, port);
      std::cout << "received" << std::endl;
    }

    sf::sleep(sf::milliseconds(2000));
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
