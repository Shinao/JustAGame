#include "GUI/ListBox.hh"

ListBox::ListBox(Menu *menu, Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale),
  _menu(menu)
{
}

ListBox::~ListBox()
{
}

void			ListBox::draw(sf::RenderWindow &win)
{
  Item::draw(win);
}

void			ListBox::designChanged()
{
  Item::designChanged();

  if (!_release && _pressed)
  {
  }
  else if (_focused)
  {
  }
  else
  {
  }
}

void			ListBox::update()
{

  designChanged();
}

Rect			ListBox::getRectRessource() const
{
  return (_rec);
}
