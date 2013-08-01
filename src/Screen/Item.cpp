#include "Screen/Item.hh"

Item::Item(Theme *theme)
{
}

Item::~Item()
{
}

void			Item::setTheme(Theme *theme)
{
  _theme = theme;
}

const Rect		&Item::getRect() const
{
  return (_rec);
}

void			Item::setRect(const Rect &rec)
{
  _rec = rec;
}
