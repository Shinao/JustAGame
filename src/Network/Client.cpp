# include "Network/Client.hh"

Client::Client() :
  _socket(NULL)
{
}

Client::~Client()
{
  if (_socket != NULL)
    delete _socket;
}

sf::TcpSocket			&Client::getSocket()
{
  return (*_socket);
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

void				Client::setSocket(sf::TcpSocket *socket)
{
  _socket = socket;
}
