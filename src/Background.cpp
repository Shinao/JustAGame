#include "Background.hh"
#include "jag.hh"
#include "GUI/Screen.hh"

Background::Background()
{
  _rec = Rect(0, 0, Screen::getSize().x, Screen::getSize().y);
}

Background::~Background()
{
}

void			Background::pressed(int, int)
{
  Screen::moving(true);
}

void			Background::released(int, int)
{
  Screen::moving(false);
}

void			Background::minimizeWindow()
{
}

void			Background::restoreWindow()
{
}

void			Background::draw(sf::RenderWindow &window)
{
  window.clear(jag::getCurrentTheme()->c_background);
}

bool			Background::update(sf::RenderWindow &)
{
  return (true);
}

bool			Background::catchMouse()
{
  return (true);
}

void			Background::mouseLeft()
{
  Screen::moving(false);
}
