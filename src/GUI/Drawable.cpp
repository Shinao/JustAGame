#include "GUI/Drawable.hh"
#include "GUI/Tooltip.hh"
#include "GUI/Screen.hh"

Drawable::Drawable(Theme *theme) :
  _tooltip(NULL),
  _text_tooltip("")
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
  removeTooltip();

  if (!_focused)
  {
    _focused = true;
    designChanged();
  }
}

void			Drawable::removeTooltip()
{
  _timer_tooltip.restart();

  if (_tooltip != NULL)
  {
    Screen::remove(_tooltip);
    _tooltip = NULL;
  }
}

void			Drawable::mouseLeft()
{
  // TODO - check if checking is really necessary
  if (_focused)
  {
    removeTooltip();
    _focused = false;
    designChanged();
  }
}

void			Drawable::draw(sf::RenderWindow &)
{
  // Check tooltip
  if (_focused && _text_tooltip != "" && _tooltip == NULL &&
      _timer_tooltip.getElapsedTime().asMilliseconds() >= DelayTooltip)
    _tooltip = new Tooltip(_text_tooltip, Screen::getCursorPosition());
}

void			Drawable::mouseReleased(int, int)
{
}

void			Drawable::setTooltip(const sf::String &text)
{
  _text_tooltip = text;
}
