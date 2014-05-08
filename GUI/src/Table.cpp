#include "Table.hh"
#include <iostream>

Table::Table(int nb_row, Theme *theme) :
  Drawable(theme)
{
  init(nb_row);
}

Table::~Table()
{
}

void			Table::draw(sf::RenderWindow &win)
{
  Drawable::draw(win);
  DrawableManager::draw(win);
}

void			Table::designChanged()
{
}

void			Table::update()
{
  designChanged();
}

void			Table::addRow(const std::vector<Item *> &items)
{
  for (unsigned i = 0; i < items.size(); ++i)
  {
    _menus[i]->add(items[i]);
    _menus[i]->update();
  }
}

void			Table::init(int nb_column)
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
    menu->addItemsCallback([&, menu](){
	for (auto menu_other : _menus)
	    menu_other->setIndexState(menu->getIndex(menu->getFocused()), Drawable::Focused);
    }, Drawable::Focused);

    menu->addItemsCallback([&, menu](){
	for (auto menu_other : _menus)
	    menu_other->setIndexState(menu->getIndex(menu->getFocused()), Drawable::Unfocused);
    }, Drawable::Unfocused);

    menu->addItemsCallback([&, menu](){
	for (auto menu_other : _menus)
	    menu_other->setIndexState(menu->getIndex(menu->getPressed()), Drawable::Pressed);
    }, Drawable::Pressed);

    menu->addItemsCallback([&, menu](){
	for (auto menu_other : _menus)
	    menu_other->setIndexState(menu->getIndex(menu->getPressed()), Drawable::Released);
    }, Drawable::Released);
  }
}

void		Table::mouseCaught(int x, int y)
{
  Drawable::mouseCaught(x, y);
  DrawableManager::mouseCaught(x, y);
}

void		Table::mouseLeft()
{
  Drawable::mouseLeft();
  DrawableManager::mouseLeft();
}

void		Table::mouseReleased(int x, int y)
{
  Drawable::mouseReleased(x, y);
  DrawableManager::mouseReleased(x, y);
}

void		Table::setRect(const Rect &rec)
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

Rect		Table::getRect() const
{
  Rect rec = _rec;

  rec.height = _menus[0]->getRect().height;
  return (rec);
}

Item		*Table::getSelectedItem(int row)
{
  return (_menus[row]->getPressed());
}

int		Table::getSelectedIndex() const
{
  return (_menus[0]->getSelectedIndex());
}
