#include "GameLayer.hh"

GameLayer::GameLayer() :
  MainMenuItem("GAME")
{
}

GameLayer::~GameLayer()
{
}

void			GameLayer::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			GameLayer::draw(sf::RenderWindow &win)
{
  MainMenuItem::draw(win);
}

void			GameLayer::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}

void			GameLayer::mouseLeft()
{
  Layer::mouseLeft();
}
