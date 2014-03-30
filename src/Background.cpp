#include "Background.hh"
#include "jag.hh"
#include "GUI/Screen.hh"

Background::Background(Screen &screen) :
  Layer::Layer(screen),
  _bg(sf::Vector2f(Screen::getSize() - sf::Vector2u(jag::WindowBorderSize * 2, jag::WindowBorderSize * 2)))
{
  _rec = Rect(0, 0, Screen::getSize().x, Screen::getSize().y);
  _bg.setPosition(jag::WindowBorderSize, jag::WindowBorderSize);
  _bg.setFillColor(jag::getCurrentTheme()->c_background);
  _bg.setOutlineColor(sf::Color::Black);
  _bg.setOutlineThickness(jag::WindowBorderSize);
}

Background::~Background()
{
}

void			Background::mousePressed(int, int)
{
  Screen::setMoving(true);
}

void			Background::mouseReleased(int, int)
{
  Screen::setMoving(false);
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
