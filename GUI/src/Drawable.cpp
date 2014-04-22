#include "Drawable.hh"
#include "Tooltip.hh"
#include "Screen.hh"

Drawable::Drawable(Theme *theme) :
  _theme(theme),
  _focused(false),
  _pressed(false),
  _release(false),
  _tooltip(NULL),
  _text_tooltip("")
{
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

    if (_callback_focused)
      _callback_focused();
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
  if (_focused)
  {
    removeTooltip();
    _focused = false;
    designChanged();

    if (_callback_unfocused)
      _callback_unfocused();
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
  _pressed = true;

  if (_release)
    _pressed = false;
  else
    designChanged();

  if (_callback_pressed)
    _callback_pressed();
}

void			Drawable::setTooltip(const sf::String &text)
{
  _text_tooltip = text;
}

void			Drawable::released()
{
  if (_pressed)
  {
    _pressed = false;
    designChanged();

    if (_callback_released)
      _callback_released();
  }
}

void			Drawable::autoRelease(bool release)
{
  _release = release;
}

bool			Drawable::isFocused() const
{
  return (_focused);
}

bool			Drawable::isPressed() const
{
  return (_pressed);
}

void			Drawable::addCallback(CallbackGui callback, State state)
{
  if (state == Pressed)
    _callback_pressed = callback;
  else if (state == Released)
    _callback_released = callback;
  else if (state == Focused)
    _callback_focused = callback;
  else
    _callback_unfocused = callback;
}
