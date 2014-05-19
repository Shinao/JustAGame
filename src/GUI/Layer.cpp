#include "Layer.hh"
#include "Screen.hh"

Layer::Layer(Type type) :
  _focused(false),
  _type(type)
{
  Screen::add(this);
}

Layer::~Layer()
{
}

void			Layer::draw(sf::RenderWindow &window)
{
  DrawableManager::draw(window);
}

void			Layer::setId(unsigned id)
{
  _id = id;
}

void			Layer::mouseCaught(int x, int y)
{
  DrawableManager::mouseCaught(x, y);

  _focused = true;
}

void			Layer::mouseLeft()
{
  DrawableManager::mouseLeft();

  _focused = false;
}

bool			Layer::update(sf::RenderWindow &)
{
  return (true);
}

void			Layer::mousePressed(int, int)
{
}

void			Layer::mouseReleased(int x, int y)
{
  DrawableManager::mouseReleased(x, y);
}

bool			Layer::catchMouse() const
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

Layer::Type		Layer::getType() const
{
  return (_type);
}
