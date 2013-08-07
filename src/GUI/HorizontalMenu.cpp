#include "GUI/HorizontalMenu.hh"

HorizontalMenu::HorizontalMenu(Rect rec, Theme *theme) :
  Menu(rec, theme)
{
  themeChanged();
}

HorizontalMenu::~HorizontalMenu()
{
}

void			HorizontalMenu::draw(sf::RenderWindow &win)
{
  // Drawing border
  win.draw(_box);
  win.draw(_border);

  for (auto item : _items)
    item->draw(win);
}

Rect			HorizontalMenu::getFilledRect() const
{
  Rect	rec = _rec;

  rec.width = _filled_width;
  return (rec);
}

void			HorizontalMenu::themeChanged()
{
  _border.setFillColor(_theme->c_border);
  _box.setFillColor(_theme->c_background);
}

// Something changed - Recalculating EVERYTHING
void			HorizontalMenu::update()
{
  // Init every item
  int			x = _rec.left;

  for (auto item : _items)
  {
    if (item->getMargin() < _margin)
      item->setMargin(_margin);

    Rect		rsrc = item->getRect();

    rsrc.left = x;
    rsrc.top = _rec.top;
    rsrc.height = _rec.height;
    item->setRect(rsrc);

    x += rsrc.width;
  }

  _filled_width = x - _rec.left;

  // Init border & background
  _border.setSize(sf::Vector2f(_rec.width - _filled_width, _theme->size_border));
  _border.setPosition(sf::Vector2f(x, _rec.top + _rec.height));

  _box.setSize(sf::Vector2f(_rec.width, _rec.height));
  _box.setPosition(sf::Vector2f(_rec.left, _rec.top));
}
