#include "GUI/Item.hh"
#include "Utility/Graphic.hh"

Item::Item(Theme *theme, Alignment align, float scale) :
  _pressed(false),
  _release(false),
  _align(align),
  _scale(scale),
  _border_type(Border::None)
{
  _focused = false;
  _theme = theme;
}

Item::~Item()
{
}

void			Item::mouseReleased(int, int)
{
  if (!_pressed)
  {
    _pressed = true;
    designChanged();

    if (_callback_pressed)
      _callback_pressed();

    if (_release)
      _pressed = false;
  }
}

void			Item::released()
{
  if (_pressed)
  {
    _pressed = false;
    designChanged();

    if (_callback_released)
      _callback_released();
  }
}

void			Item::designChanged()
{
  unsigned		size_border;

  if (!_release && _pressed)
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
  Utility::initBorderByType(_border, _rec, size_border, _border_type);
}

void			Item::draw(sf::RenderWindow &win)
{
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

void			Item::addCallback(Callback callback, State state)
{
  if (state == Pressed)
    _callback_pressed = callback;
  else
    _callback_released = callback;
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
    pos.x += rsrc.width / 2 + _margin.x;
  else
    pos.x += rsrc.width + _margin.x;

  // Always align vertically
  pos.y += (_rec.height - rsrc.height) / 2;

  return (pos);
}

bool			Item::isFocused() const
{
  return (_focused);
}

bool			Item::isPressed() const
{
  return (_pressed);
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

void			Item::autoRelease(bool release)
{
  _release = release;
}

void			Item::setBorder(Border::Type border)
{
  _border_type = border;
}
