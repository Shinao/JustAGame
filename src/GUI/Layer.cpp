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
  // Clear Drawables
  for (auto drawable : _drawables)
    delete drawable.second;
}

void			Layer::addDrawable(Drawable *drawable, std::string name)
{
  _drawables[name] = drawable;
}

void			Layer::draw(sf::RenderWindow &window)
{
  // Draw all Drawables
  for (auto drawable : _drawables)
    drawable.second->draw(window);
}

Drawable		*Layer::getDrawable(std::string name)
{
  return (_drawables[name]);
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
