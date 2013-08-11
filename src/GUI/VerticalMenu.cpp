#include "GUI/VerticalMenu.hh"
#include "Utility/Graphic.hh"

VerticalMenu::VerticalMenu(Rect rec, Theme *theme) :
  Menu(rec, theme)
{
  themeChanged();
}

VerticalMenu::~VerticalMenu()
{
}

Rect			VerticalMenu::getFilledRect() const
{
  Rect	rec = _rec;

  rec.height = _filled_height;
  return (rec);
}

// Something changed - Recalculating EVERYTHING
void			VerticalMenu::update()
{
  // Init every item
  int			y = _rec.top;

  for (auto item : _items)
  {
    item->setMargin(_margin);

    Rect		rsrc = item->getRect();

    rsrc.top = y;
    rsrc.left = _rec.left;
    rsrc.width = _rec.width;
    item->setRect(rsrc);

    y += rsrc.height;
  }

  // Updating filled area
  _filled_height = y - _rec.top;

  // Init box and border
  Utility::initBorderByType(_border, _rec, _theme->size_border, _border_type);

  _box.setSize(sf::Vector2f(_rec.width, _rec.height));
  _box.setPosition(sf::Vector2f(_rec.left, _rec.top));
}
