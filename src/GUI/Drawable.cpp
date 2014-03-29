#include "GUI/Drawable.hh"

void		Drawable::setTheme(Theme *theme)
{
  _theme = theme;
  designChanged();
}
