#include "GUI/Drawable.hh"
#include "GUI/Tooltip.hh"
#include "GUI/Screen.hh"

Drawable::Drawable(Theme *theme)
{
  _theme = theme;
}

void			Drawable::setTheme(Theme *theme)
{
  _theme = theme;
  designChanged();
}

Theme			*Drawable::getTheme()
{
  return (_theme);
}

void			Drawable::setRect(const Rect &rec)
{
  _rec = rec;

  update();
}

Rect			Drawable::getRect() const
{
  return (_rec);
}

void			Drawable::mouseCaught(int, int)
{
  if (!_focused)
  {
    _focused = true;
    designChanged();
  }
}

void			Drawable::mouseLeft()
{
  // TODO - check if checking is really necessary
  if (_focused)
  {
    _focused = false;
    designChanged();
  }
}

void			Drawable::mouseReleased(int, int)
{
}

void			Drawable::setTooltip(const sf::String text, const sf::Vector2i &pos)
{
  Screen::add(new Tooltip(text, pos));
}
