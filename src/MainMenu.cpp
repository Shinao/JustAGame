#include "MainMenu.hh"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
  delete _menu;
}

void			MainMenu::released(int x, int y)
{
  if (_menu->getRect().contains(x, y))
    _menu->clicked();
}

void			MainMenu::draw(sf::RenderWindow &window)
{
  _menu->draw(window);
}

bool			MainMenu::update(sf::RenderWindow &)
{
  return (true);
}

bool			MainMenu::catchMouse()
{
  return (true);
}
