#include "Screen.hh"
#include "Tooltip.hh"
#include "jag.hh"

Tooltip::Tooltip(const sf::String &text, const sf::Vector2i &pos) :
  Layer(Layer::Other)
{
  _string = new String(text, jag::getTheme("Tooltip"));
  _string->setMargin(sf::Vector2i(8, 0));
  int string_width = _string->getRect().width;

  // Get best position from position and size window to avoid out of bounds
  if (pos.y > (int) Screen::getSize().y / 2)
  {
    _bar.setPosition(pos.x, pos.y - SpaceFromCursor);
    _bar.setSize(sf::Vector2f(BarSize, SpaceFromCursor));

    if (pos.x > (int) Screen::getSize().x / 2)
      _string->setRect(Rect(pos.x - string_width, pos.y - SpaceFromCursor, string_width, StringHeight));
    else
      _string->setRect(Rect(pos.x + BarSize, pos.y - SpaceFromCursor, string_width, StringHeight));
  }
  else
  {
    _bar.setPosition(pos.x, pos.y);
    _bar.setSize(sf::Vector2f(BarSize, SpaceFromCursor));

    if (pos.x > (int) Screen::getSize().x / 2)
      _string->setRect(Rect(pos.x - string_width, pos.y + SpaceFromCursor - StringHeight, 
	    string_width, StringHeight));
    else
      _string->setRect(Rect(pos.x + BarSize, pos.y + SpaceFromCursor - StringHeight, string_width, StringHeight));
  }

  _bar.setFillColor(jag::getTheme("Tooltip")->c_border);
}

Tooltip::~Tooltip()
{
  delete _string;
}

bool			Tooltip::catchMouse() const
{
  return (false);
}

void			Tooltip::draw(sf::RenderWindow &window)
{
  _string->draw(window);
  window.draw(_bar);
}
