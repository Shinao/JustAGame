#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <pthread.h>
#include "Network.hh"
#include <SFML/Network.hpp>

void	newClient(ProtocoledPacket &packet)
{
  std::cout << "new client" << std::endl;
}

int	main(int ac, char **av)
{
  Network::init(52025, false);
  using namespace std::placeholders;
  Network::addRequest(Request::Connexion, std::bind(newClient, _1));

  sf::TcpSocket *socket = new sf::TcpSocket();
  socket->connect("127.0.0.1", 25052);
  Client *client = new Client();
  client->setSocket(socket);
  client->setPort(25052);
  Network::addClient(client);

  while (1)
  {
    Network::update();
  }
}
