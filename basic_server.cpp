#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <pthread.h>
#include "Network.hh"

void	newClient(ProtocoledPacket &packet)
{
  std::cout << "New client callback called" << std::endl;
}

void	bye(ProtocoledPacket &packet)
{
  std::cout << "Bye callback called" << std::endl;
}

void	test(ProtocoledPacket &packet)
{
  std::string str;
  packet >> str;
  std::cout << "test received : " << str << std::endl;
}

int	main(int ac, char **av)
{
  Network::init(25052, true);
  using namespace std::placeholders;
  Network::addRequest(Request::Connexion, std::bind(newClient, _1));
  Network::addRequest(Request::Test, std::bind(test, _1));
  Network::addRequest(Request::Disconnexion, std::bind(bye, _1));

  while (1)
  {
    Network::update();
  }
}
