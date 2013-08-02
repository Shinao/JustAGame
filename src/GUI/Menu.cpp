#include "GUI/Menu.hh"

Menu::Menu(Rect rec, Theme *theme)
  : _rec(rec),
  _theme(theme),
  _item_focused(NULL)
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

// Checking on all items and send a signal
void			Menu::mouseCaught(int x, int y)
{
  // Check if still on same item
  if (_item_focused != NULL)
  {
    if (_item_focused->getRect().contains(x, y))
    {
      _item_focused->mouseCaught(x, y);
      return ;
    }
    // Not found
    _item_focused->mouseLeft();
    _item_focused = NULL;
  }

  // Checking on all items
  for (auto item : _items)
    if (item->getRect().contains(x, y))
    {
      item->mouseCaught(x, y);
      _item_focused = item;
      return ;
    }
}

void			Menu::mouseLeft()
{
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
