#include "GUI/Layer.hh"
#include "GUI/Screen.hh"

Layer::Layer()
{
}

Layer::~Layer()
{
  auto			&map = Screen::getMap();

  for (int i = 0; i < _actions.size(); ++i)
    map.removeAction(i);
}

int			Layer::actionId()
{
  int			id = Screen::actionId();

  _actions.push_back(id);
  return (id);
}

void			Layer::setId(unsigned id)
{
  _id = id;
}

void			Layer::mouseCaught(int x, int y) {}

void			Layer::mouseLeft() {}

bool			Layer::textEntered(sf::Uint32)
{
  return (false);
}

bool			Layer::update(sf::RenderWindow &)
{
  return (false);
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
