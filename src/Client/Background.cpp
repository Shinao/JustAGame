#include "Background.hh"
#include "jag.hh"
#include "Screen.hh"

Background::Background() :
  Layer(Layer::Setting),
  _bg(sf::Vector2f(Screen::getSize() - sf::Vector2u(jag::WINDOW_BORDER_SIZE * 2, jag::WINDOW_BORDER_SIZE * 2)))
{
  _bg.setFillColor(jag::getCurrentTheme()->c_background);
  _bg.setOutlineColor(sf::Color::Black);
  _bg.setOutlineThickness(jag::WINDOW_BORDER_SIZE);
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
  _rec = Rect(Screen::getSize().x / 2 - jag::CLIENT_WIDTH / 2, Screen::getSize().y / 2 - jag::CLIENT_HEIGHT / 2, jag::CLIENT_WIDTH, jag::CLIENT_HEIGHT);
  _bg.setPosition(_rec.left + jag::WINDOW_BORDER_SIZE, _rec.top + jag::WINDOW_BORDER_SIZE);
}
