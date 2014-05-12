#include "APlayer.hh"

APlayer::APlayer() :
  _is_admin(false)
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

void			APlayer::setPing(Ping ping)
{
  _ping = ping;
}
