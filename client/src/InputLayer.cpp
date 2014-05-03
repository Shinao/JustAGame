#include "InputLayer.hh"

InputLayer::InputLayer() :
  MainMenuItem("INPUT")
{
}

InputLayer::~InputLayer()
{
}

void			InputLayer::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			InputLayer::draw(sf::RenderWindow &win)
{
  MainMenuItem::draw(win);
}

void			InputLayer::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}

void			InputLayer::mouseLeft()
{
  Layer::mouseLeft();
}
