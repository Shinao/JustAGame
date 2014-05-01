#include "Player.hh"

Player::Player()
{
}

Player::~Player()
{
}

const std::string		&Player::getName() const
{
  return (_name);
}

void				Player::setName(const std::string &name)
{
  _name = name;
}

const sf::Color			&Player::getColor() const
{
  return (_color);
}

void				Player::setColor(const sf::Color &color)
{
  _color = color;
}

void				Player::setId(ClientID id)
{
  _id = id;
}

ClientID			Player::getId() const
{
  return (_id);
}

Ping				Player::getPing() const
{
  return (_ping);
}

void			Player::setPing(Ping ping)
{
  _ping = ping;
}
