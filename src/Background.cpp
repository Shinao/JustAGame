#include "Background.hh"
#include "jag.hh"
#include "GUI/Screen.hh"

Background::Background() :
  _bg(sf::Vector2f(Screen::getSize() - sf::Vector2u(jag::WindowBorderSize * 2, jag::WindowBorderSize * 2)))
{
  _rec = Rect(0, 0, Screen::getSize().x, Screen::getSize().y);
  _bg.setPosition(1, 1);
  _bg.setFillColor(jag::getCurrentTheme()->c_background);
  _bg.setOutlineColor(jag::getCurrentTheme()->c_border);
  _bg.setOutlineThickness(jag::WindowBorderSize);
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

void			Background::draw(sf::RenderWindow &window)
{
  window.draw(_bg);
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
