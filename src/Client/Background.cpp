#include "Background.hh"
#include "jag.hh"
#include "Screen.hh"

Background::Background() :
  Layer(Layer::Setting),
  _bg(sf::Vector2f(Screen::getSize() - sf::Vector2u(jag::WindowBorderSize * 2, jag::WindowBorderSize * 2)))
{
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

void			Background::settingChanged()
{
  _rec = Rect(Screen::getSize().x / 2 - jag::ClientWidth / 2, Screen::getSize().y / 2 - jag::ClientHeight / 2, jag::ClientWidth, jag::ClientHeight);
  _bg.setPosition(_rec.left + jag::WindowBorderSize, _rec.top + jag::WindowBorderSize);
}
