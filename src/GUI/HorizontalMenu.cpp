#include "GUI/HorizontalMenu.hh"

HorizontalMenu::HorizontalMenu(Rect rec, Theme *theme)
  : Menu(rec, theme)
{
  // Init border
  _border.setSize(sf::Vector2f(_rec.width, _theme->size_border));
  _border.setPosition(sf::Vector2f(_rec.left, _rec.top + _rec.height));
  _border.setFillColor(_theme->c_border);

  _box.setSize(sf::Vector2f(_rec.width, _rec.height));
  _box.setPosition(sf::Vector2f(_rec.left, _rec.top));
  _box.setFillColor(_theme->c_background);
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

// Something changed - Recalculating EVERYTHING
void			HorizontalMenu::update()
{
  // Init every item
  int			x = _rec.left;

  for (auto item : _items)
  {
    Rect		rec = item->getRect();

    rec.left = x;
    rec.top = _rec.top;
    rec.height = _rec.height;
    item->setRect(rec);

    x += rec.width;
  }
}
