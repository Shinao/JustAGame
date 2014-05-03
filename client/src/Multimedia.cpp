#include "Multimedia.hh"

Multimedia::Multimedia() :
  MainMenuItem("MULTIMEDIA")
{
}

Multimedia::~Multimedia()
{
}

void			Multimedia::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			Multimedia::draw(sf::RenderWindow &win)
{
  MainMenuItem::draw(win);
}

void			Multimedia::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}

void			Multimedia::mouseLeft()
{
  Layer::mouseLeft();
}
