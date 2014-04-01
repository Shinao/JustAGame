#include "KeyBinding.hh"
#include "GUI/Screen.hh"

KeyBinding::KeyBinding() :
  Layer::Layer()
{
}

KeyBinding::~KeyBinding()
{
}

void			KeyBinding::mouseReleased(int, int)
{
}

void			KeyBinding::draw(sf::RenderWindow &)
{
}

void			KeyBinding::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);

}

void			KeyBinding::mouseLeft()
{
  Layer::mouseLeft();

}
