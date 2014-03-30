#include "GUI/Drawable.hh"

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
