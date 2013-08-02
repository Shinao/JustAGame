#include "GUI/Screen.hh"
#include "GUI/Menu.hh"

Menu::Menu(Rect rec, Theme *theme)
  : _rec(rec),
  _theme(theme),
  _item_focused(NULL),
  _item_pressed(NULL)
{
  // Catching click
  int id = actionId();
  Screen::getMap()[id] = thor::Action(sf::Mouse::Left, thor::Action::PressOnce);
  Screen::getSystem().connect(id, std::bind(&Menu::clicked, this));
}

Menu::~Menu()
{
  for (auto item : _items)
    delete item;
}

// Intercepted click - send it to item focused
void			Menu::clicked()
{
  // Toggle pressed
  if (_item_focused != NULL)
  {
    if (_item_pressed != NULL && _item_pressed != _item_focused)
      _item_pressed->unPressed();

    _item_focused->pressed();
    _item_pressed = _item_focused;
  }
}

bool			Menu::textEntered(const std::string &str)
{
  if (_item_pressed != NULL)
    return (_item_pressed->textEntered(str));
  return (false);
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

int			Menu::getFocused() const
{
  if (_item_focused == NULL)
    return (-1);
  return (_item_focused->getId());
}

int			Menu::getPressed() const
{
  if (_item_pressed == NULL)
    return (-1);
  return (_item_pressed->getId());
}
