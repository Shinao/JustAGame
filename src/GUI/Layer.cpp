#include "GUI/Layer.hh"
#include "GUI/Screen.hh"

Layer::Layer() :
  _focused(false)
{
}

Layer::~Layer()
{
}

void			Layer::setId(unsigned id)
{
  _id = id;
}

void			Layer::mouseCaught(int, int)
{
  _focused = true;
}

void			Layer::mouseLeft()
{
  _focused = false;
}

bool			Layer::textEntered(const std::string &)
{
  return (false);
}

bool			Layer::update(sf::RenderWindow &)
{
  return (true);
}

void			Layer::clicked(int, int)
{
}

bool			Layer::catchMouse()
{
  return (true);
}

unsigned		Layer::getId() const
{
  return (_id);
}

const Rect		&Layer::getRect() const
{
  return (_rec);
}
