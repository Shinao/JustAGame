#include "GUI/Table.hh"
#include <iostream>

Table::Table(int nb_row, Theme *theme) :
  Drawable(theme)
{
  init(nb_row);
}

Table::~Table()
{
}

void				Table::draw(sf::RenderWindow &win)
{
  Drawable::draw(win);
  DrawableManager::draw(win);
}

void				Table::designChanged()
{
}

void				Table::update()
{
  designChanged();
}

void				Table::addRow(const std::vector<Item *> &items)
{
  for (unsigned i = 0; i < items.size(); ++i)
  {
    _menus[i]->add(items[i]);
    _menus[i]->update();
  }
}

void				Table::init(int nb_column)
{
  Menu	*menu;
  int	width = _rec.width / nb_column;
  int	x = _rec.left;

  for (int i = 0; i < nb_column; ++i)
  {
    menu = new Menu(Menu::Vertical, _theme);
    menu->shrinkToFit(true);
    menu->setMargin(sf::Vector2i(0, 12));
    menu->setRect(Rect(x, _rec.top, width, _rec.height));
    _menus.push_back(menu);
    add(menu);

    x += width;
  }

  // Add event for each menu - One event to rull them ALL
  for (auto menu : _menus)
  {
    reflectMenu(menu, Focused);
    reflectMenu(menu, Unfocused);
    reflectMenu(menu, Pressed);
    reflectMenu(menu, Released);
  }
}

// TODO - Problem focus unfocus same item
void				Table::reflectMenu(Menu *menu, State state)
{
  menu->addItemsCallback([&, menu, state](){
    for (auto menu_other : _menus)
    {
    	// Don't call our callback caller (mindfuck)
    	if (menu_other == menu)
     	  continue ;

	Item *item = ((state == Focused || state == Unfocused) ? menu->getFocused() : menu->getPressed());
     	menu_other->setIndexState(menu->getIndex(item), state);
    }

    if (state == Focused && _cb_item_focused)
    _cb_item_focused();
    else if (state == Unfocused && _cb_item_unfocused)
    _cb_item_unfocused();
    else if (state == Pressed && _cb_item_pressed)
    _cb_item_pressed();
    else if (_cb_item_released)
    _cb_item_released();
  }, state);
}

void				Table::mouseCaught(int x, int y)
{
  Drawable::mouseCaught(x, y);
  DrawableManager::mouseCaught(x, y);
}

void				Table::mouseLeft()
{
  Drawable::mouseLeft();
  DrawableManager::mouseLeft();
}

void				Table::mouseReleased(int x, int y)
{
  Drawable::mouseReleased(x, y);
  DrawableManager::mouseReleased(x, y);
}

void				Table::setRect(const Rect &rec)
{
  Drawable::setRect(rec);

  int	width = _rec.width / _menus.size();
  int	x = _rec.left;

  for (auto menu : _menus)
  {
    menu->setRect(Rect(x, _rec.top, width, _rec.height));
    x += width;
  }
}

Rect				Table::getRect() const
{
  Rect rec = _rec;

  rec.height = _menus[0]->getRect().height;
  return (rec);
}

Item				*Table::getSelectedItem(int row)
{
  return (_menus[row]->getPressed());
}

int				Table::getSelectedIndex() const
{
  return (_menus[0]->getSelectedIndex());
}

void				Table::unselect()
{
  int	index = _menus[0]->getSelectedIndex();

  if (index != -1)
  {
    for (auto menu : _menus)
      menu->setIndexState(index, Released);
  }
}

void				Table::addItemsCallback(CallbackGui cb, State state)
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
