#include "KeyBinding.hh"
#include "Screen.hh"

KeyBinding::KeyBinding() :
  Layer::Layer()
{
}

KeyBinding::~KeyBinding()
{
}

void			KeyBinding::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
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
