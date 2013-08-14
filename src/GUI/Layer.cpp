#include "GUI/Layer.hh"
#include "GUI/Screen.hh"

Layer::Layer(Screen &screen) :
  _screen(screen),
  _focused(false)
{
  screen.add(this);
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

void			Layer::pressed(int, int)
{
}

void			Layer::released(int, int)
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
