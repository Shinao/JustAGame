#include "GUI/Screen.hh"
#include "GUI/Menu.hh"
#include "Utility/Graphic.hh"

Menu::Menu(Type type, Rect rec, Theme *theme) :
  _type(type),
  _border_type(Border::None),
  _item_focused(NULL),
  _item_pressed(NULL),
  _shrink(false)
{
  _focused = false;
  _theme = theme;
  _rec = rec;
}

Menu::~Menu()
{
  for (auto item : _items)
    delete item;
}

void			Menu::draw(sf::RenderWindow &win)
{
  // Drawing background and border
  win.draw(_box);
  win.draw(_border);

  // Draw each item
  for (auto item : _items)
    item->draw(win);
}

// Something changed - Recalculating EVERYTHING
void			Menu::update()
{
  // Depending on the type - we fill only one side
  int			filled;
  if (_type == Horizontal)
    filled = _rec.left;
  else
    filled = _rec.top;

  // Init every item
  for (auto item : _items)
  {
    item->setMargin(_margin);

    Rect		rsrc = item->getRect();

    if (_type == Horizontal)
    {
      rsrc.left = filled;
      rsrc.top = _rec.top;
      rsrc.height = _rec.height;

      filled += rsrc.width;
    }
    else
    {
      rsrc.top = filled;
      rsrc.left = _rec.left;
      rsrc.width = _rec.width;

      filled += rsrc.height;
    }

    item->setRect(rsrc);
  }

  // Shrink if needed
  if (_shrink)
  {
    if (_type == Horizontal)
      _rec.width = filled - _rec.left;
    else
      _rec.height = filled - _rec.top;
  }

  // Init box and border
  Utility::initBorderByType(_border, _rec, _theme->size_border, _border_type);

  _box.setSize(sf::Vector2f(_rec.width, _rec.height));
  _box.setPosition(sf::Vector2f(_rec.left, _rec.top));

  designChanged();
}

// Intercepted click - send it to item focused
void			Menu::mouseReleased(int x, int y)
{
  // Toggle pressed
  if (_item_focused != NULL)
  {
    if (_item_pressed != NULL && _item_pressed != _item_focused)
      _item_pressed->released();

    _item_focused->mouseReleased(x, y);
    _item_pressed = _item_focused;
  }
}

void			Menu::add(Item *item)
{
  _items.push_back(item);

  // Update item
  if (item->getTheme() == NULL)
    item->setTheme(_theme);
  item->setBorder(_border_type);

  item->mouseLeft();
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

void			Menu::setMargin(const sf::Vector2i &margin)
{
  _margin = margin;
}

void			Menu::mouseLeft()
{
  if (_item_focused != NULL)
    _item_focused->mouseLeft();
}

void			Menu::remove(Item *item)
{
  for (auto it = _items.begin(); it != _items.end(); ++it)
    if ((*it) == item)
      _items.erase(it);
}

void			Menu::setTheme(Theme *theme)
{
  Drawable::setTheme(theme);

  for (auto item : _items)
    item->setTheme(theme);
}

void			Menu::setPressed(Item *item)
{
  _item_pressed = item;
  item->mouseReleased(0, 0);
}

void			Menu::setBorder(Border::Type border)
{
  _border_type = border;

  // Tell each item to add this type of border
  for (auto item : _items)
    item->setBorder(border);
}

void			Menu::designChanged()
{
  _border.setFillColor(_theme->c_border);
  _box.setFillColor(_theme->c_background);
}

void			Menu::shrinkToFit(bool shrink)
{
  _shrink = shrink;
}
