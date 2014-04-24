#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <pthread.h>
#include "Network.hh"

void	newClient(ProtocoledPacket &packet)
{
  std::cout << "new client" << std::endl;
}

int	main(int ac, char **av)
{
  Network::init(25052, true);
  using namespace std::placeholders;
  Network::addRequest(Request::Connexion, std::bind(newClient, _1));

  while (1)
  {
    Network::update();
  }
}
