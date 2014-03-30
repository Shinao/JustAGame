#include "KeyBinding.hh"
#include "GUI/Screen.hh"

KeyBinding::KeyBinding(Screen &screen) :
  Layer::Layer(screen)
{
}

KeyBinding::~KeyBinding()
{
}

void			KeyBinding::mouseReleased(int, int)
{
}

void			KeyBinding::draw(sf::RenderWindow &window)
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
