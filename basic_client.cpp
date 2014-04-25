#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <pthread.h>
#include "Network.hh"
#include <SFML/Network.hpp>

void	newClient(ProtocoledPacket &packet)
{
  std::cout << "new client" << std::endl;

  ProtocoledPacket *test = new ProtocoledPacket(packet.getClient(), Request::Test, Network::Unreliable);
  *test << "Bonjour";
  Network::send(test);
}

void	test(ProtocoledPacket &packet)
{
  std::cout << "test received wtf" << std::endl;
}

int	main(int ac, char **av)
{
  Network::init(52025, false);
  using namespace std::placeholders;
  Network::addRequest(Request::Connexion, std::bind(newClient, _1));
  Network::addRequest(Request::Test, std::bind(test, _1));

  Client *client = new Client();
  client->setIp("127.0.0.1");
  client->setPort(25052);
  Network::connect(client);

  while (1)
  {
    Network::update();
  }
}
