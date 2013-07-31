#include "Screen/Layer.hh"

Layer::Layer()
{
}

Layer::~Layer()
{
}

void			Layer::setId(unsigned id)
{
  _id = id;
}

void			Layer::mouseMoved(int x, int y) {}

void			Layer::mouseLeft() {}

bool			Layer::catchEvent(sf::Event &)
{
  return (false);
}

bool			Layer::textEntered()
{
  return (false);
}

unsigned		Layer::getId() const
{
  return (_id);
}

int			Layer::getX() const
{
  return (_x);
}

int			Layer::getY() const
{
  return (_y);
}

int			Layer::getWidth() const
{
  return (_width);
}

int			Layer::getHeight() const
{
  return (_height);
}
