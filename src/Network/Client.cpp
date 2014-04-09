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

ClientID			Client::getId() const
{
  return (_id);
}

void				Client::setId(ClientID id)
{
  _id = id;
}

const sf::IpAddress		Client::getIp() const
{
  return (_ip);
}

void				Client::setIp(const sf::IpAddress &ip)
{
  _ip = ip;
}
