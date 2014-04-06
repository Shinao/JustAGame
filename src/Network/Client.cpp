# include "Network/Client.hh"

Client::Client()
{
}

Client::~Client()
{
}

sf::TcpSocket			&Client::getSocket()
{
  return (_socket);
}
