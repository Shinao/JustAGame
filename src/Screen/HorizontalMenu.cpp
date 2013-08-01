#include "Screen/HorizontalMenu.hh"

HorizontalMenu::~HorizontalMenu()
{
}

void			HorizontalMenu::draw(sf::RenderWindow &win)
{
  for (auto item : _items)
    item->draw(win);
}

// Something changed - Recalculing EVERYTHING
void			HorizontalMenu::update()
{
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
