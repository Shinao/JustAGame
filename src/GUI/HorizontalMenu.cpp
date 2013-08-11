#include "GUI/HorizontalMenu.hh"
#include "Utility/Graphic.hh"

HorizontalMenu::HorizontalMenu(Rect rec, Theme *theme) :
  Menu(rec, theme)
{
  themeChanged();
}

HorizontalMenu::~HorizontalMenu()
{
}

Rect			HorizontalMenu::getFilledRect() const
{
  Rect	rec = _rec;

  rec.width = _filled_width;
  return (rec);
}

// Something changed - Recalculating EVERYTHING
void			HorizontalMenu::update()
{
  // Init every item
  int			x = _rec.left;

  for (auto item : _items)
  {
    item->setMargin(_margin);

    Rect		rsrc = item->getRect();

    rsrc.left = x;
    rsrc.top = _rec.top;
    rsrc.height = _rec.height;
    item->setRect(rsrc);

    x += rsrc.width;
  }

  // Updating filled area
  _filled_width = x - _rec.left;

  // Init box and border
  Utility::initBorderByType(_border, _rec, _theme->size_border, _border_type);

  _box.setSize(sf::Vector2f(_rec.width, _rec.height));
  _box.setPosition(sf::Vector2f(_rec.left, _rec.top));
}
