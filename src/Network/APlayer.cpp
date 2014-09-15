#include "Network/APlayer.hh"

APlayer::APlayer() :
  _ping(0),
  _is_admin(false),
  _client(NULL)
{
}

APlayer::~APlayer()
{
}

const std::string		&APlayer::getName() const
{
  return (_name);
}

void				APlayer::setName(const std::string &name)
{
  _name = name;
}

const sf::Color			&APlayer::getColor() const
{
  return (_color);
}

void				APlayer::setColor(const sf::Color &color)
{
  _color = color;
}

void				APlayer::setId(ClientID id)
{
  _id = id;
}

ClientID			APlayer::getId() const
{
  return (_id);
}

Ping				APlayer::getPing() const
{
  return (_ping);
}

void				APlayer::setPing(Ping ping)
{
  _ping = ping;
}

void				APlayer::setClient(Client *client)
{
  _client = client;
}

Client				*APlayer::getClient()
{
  return (_client);
}
