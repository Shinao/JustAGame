#include "Screen/Menu.hh"

Menu::Menu(Rect rec, Theme *theme)
  : _rec(rec),
  _theme(theme)
{
}

Menu::~Menu()
{
  for (auto item : _items)
    delete item;
}

void			Menu::add(Item *item)
{
  _items.push_back(item);
  update();
}

void			Menu::remove(Item *item)
{
  for (auto it = _items.begin(); it != _items.end(); ++it)
    if ((*it) == item)
      _items.erase(it);

  update();
}

const Rect		&Menu::getRect() const
{
  return (_rec);
}

void			Menu::setRect(const Rect &rec)
{
  _rec = rec;
}

void			Menu::setTheme(Theme *theme)
{
  _theme = theme;
  for (auto item : _items)
    item->setTheme(theme);
}
