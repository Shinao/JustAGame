#include "Screen.hh"
#include "Menu.hh"
#include "Utility/Graphic.hh"

Menu::Menu(Type type, Theme *theme) :
  Drawable(theme),
  _type(type),
  _border_type(Border::None),
  _item_focused(NULL),
  _item_pressed(NULL),
  _shrink(false)
{
  _focused = false;
}

Menu::~Menu()
{
  for (auto item : _items)
    delete item;
}

void			Menu::draw(sf::RenderWindow &win)
{
  Drawable::draw(win);

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
    {
      _item_pressed->released();
    if (_cb_item_released)
      _cb_item_released();
    }

    _item_focused->mouseReleased(x, y);
    _item_pressed = _item_focused;
    if (_cb_item_pressed)
      _cb_item_pressed();
  }

  Drawable::mouseReleased(x, y);
}

void			Menu::add(Item *item)
{
  _items.push_back(item);

  item->setBorder(_border_type);
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
      Drawable::mouseCaught(x, y);
      return ;
    }
    // Not found
    _item_focused->mouseLeft();
    _item_focused = NULL;

    if (_cb_item_unfocused)
      _cb_item_unfocused();
  }

  // Checking on all items
  for (auto item : _items)
    if (item->getRect().contains(x, y))
    {
      item->mouseCaught(x, y);
      _item_focused = item;

      if (_cb_item_focused)
	_cb_item_focused();

      break ;
    }

  Drawable::mouseCaught(x, y);
}

void			Menu::setMargin(const sf::Vector2i &margin)
{
  _margin = margin;
}

void			Menu::mouseLeft()
{
  if (_item_focused != NULL)
  {
    _item_focused->mouseLeft();

    if (_cb_item_unfocused)
      _cb_item_unfocused();
  }

  Drawable::mouseLeft();
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

Item			*Menu::getFocused()
{
  return (_item_focused);
}

Item			*Menu::getPressed()
{
  return (_item_pressed);
}

void			Menu::addItemsCallback(CallbackGui cb, State state)
{
  if (state == Focused)
    _cb_item_focused = cb;
  else if (state == Unfocused)
    _cb_item_unfocused = cb;
  else if (state == Pressed)
    _cb_item_pressed = cb;
  else
    _cb_item_released = cb;
}

void			Menu::setIndexState(int index, State state)
{
  if ((state == Focused || state == Unfocused) && _item_focused != NULL)
  {
    _item_focused->mouseLeft();
    _item_focused = NULL;
  }
  if ((state == Pressed || state == Released) && _item_pressed != NULL)
  {
    _item_pressed->released();
    _item_pressed = NULL;
  }

  if (state == Focused)
  {
    _item_focused = _items[index];
    _item_focused->mouseCaught(0, 0);
  }
  else if (state == Pressed)
  {
    _item_pressed = _items[index];
    _item_pressed->mouseReleased(0, 0);
  }
}

int			Menu::getIndex(Item *search)
{
  for (unsigned i = 0; i < _items.size(); ++i)
    if (_items[i] == search)
      return (i);

  return (-1);
}
