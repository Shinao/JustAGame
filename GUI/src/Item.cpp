#include "Item.hh"
#include "Utility/Graphic.hh"

Item::Item(Theme *theme, Alignment align, float scale) :
  _align(align),
  _scale(scale)
{
  _theme = theme;
}

Item::~Item()
{
}

void			Item::mouseReleased(int x, int y)
{
  Drawable::mouseReleased(x, y);
}

void			Item::released()
{
  Drawable::released();
}

void			Item::designChanged()
{
  unsigned		size_border;

  if (_pressed)
  {
    _border.setFillColor(_theme->c_border_pressed);
    size_border = _theme->size_border_pressed;

    _box.setFillColor(_theme->c_background_pressed);
  }
  else if (_focused)
  {
    _border.setFillColor(_theme->c_border_focused);
    size_border = _theme->size_border_focused;

    _box.setFillColor(_theme->c_background_focused);
  }
  else
  {
    _border.setFillColor(_theme->c_border);
    size_border = _theme->size_border;

    _box.setFillColor(_theme->c_background);
  }

  // Size of the border changed - set position according to the type of the border
  Utility::initBorderByType(_border, _rec, size_border, _theme->border);
}

void			Item::draw(sf::RenderWindow &win)
{
  Drawable::draw(win);

  win.draw(_box);
  win.draw(_border);
}

Rect			Item::getRect() const
{
  Rect			rsrc = getRectRessource();

  rsrc.width += _margin.x * 2;
  rsrc.height += _margin.y * 2;
  rsrc.left = _rec.left;
  rsrc.top = _rec.top;

  // Depending on Vertical or Horizontal Menu
  // We keep the largest size
  if (rsrc.width < _rec.width)
    rsrc.width = _rec.width;
  if (rsrc.height < _rec.height)
    rsrc.height = _rec.height;

  return (rsrc);
}

void			Item::setRect(const Rect &rec)
{
  _box.setSize(sf::Vector2f(rec.width, rec.height));
  _box.setPosition(sf::Vector2f(rec.left, rec.top));

  Drawable::setRect(rec);
}

sf::Vector2i		Item::getRessourcePosition()
{
  sf::Vector2i		pos;

  // Getting width & height depending on text
  auto			rsrc = getRectRessource(); 

  // Getting x depending on alignment
  pos.x = _rec.left;
  pos.y = _rec.top;
  if (_align == Left)
    pos.x += _margin.x;
  else if (_align == Center)
    pos.x += _rec.width / 2 - rsrc.width / 2;
  else
    pos.x += rsrc.width + _margin.x;

  // Always align vertically
  pos.y += (_rec.height - rsrc.height) / 2;

  return (pos);
}

void			Item::setAlignment(Alignment align)
{
  _align = align;
}

Item::Alignment		Item::getAlignment()
{
  return (_align);
}

const sf::Vector2i	&Item::getMargin() const
{
  return (_margin);
}

void			Item::setMargin(const sf::Vector2i &margin)
{
  _margin = margin;
}
