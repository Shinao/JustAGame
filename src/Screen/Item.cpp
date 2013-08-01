#include "Screen/Item.hh"

Item::Item(Theme *theme, Alignment align, float scale)
  : _theme(theme),
  _align(align),
  _scale(scale),
  _margin(0)
{
}

Item::~Item()
{
}

Theme			*Item::getTheme()
{
  return (_theme);
}

void			Item::draw(sf::RenderWindow &win)
{
  win.draw(_box);
}

void			Item::mouseCaught(int x, int y)
{
  _box.setFillColor(_theme->c_border_focused);
}

void			Item::mouseLeft()
{
  _box.setFillColor(_theme->c_border);
}

void			Item::setTheme(Theme *theme)
{
  _theme = theme;
}

Rect			Item::getRect() const
{
  Rect			rec = _rec;

  rec.width += _margin * 2;
  rec.height += _margin * 2;
  return (_rec);
}

const Rect		&Item::getRectRessource() const
{
  return (_rec);
}

void			Item::setRect(const Rect &rec)
{
  _rec = rec;

  _box.setSize(sf::Vector2f(_rec.width, _rec.height));
  _box.setPosition(sf::Vector2f(_rec.left, _rec.top));
}

void			Item::setAlignment(Alignment align)
{
  _align = align;
}

Item::Alignment		Item::getAlignment()
{
  return (_align);
}

int			Item::getMargin()
{
  return (_margin);
}

void			Item::setMargin(int margin)
{
  _margin = margin;
}
