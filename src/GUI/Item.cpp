#include "GUI/Item.hh"
#include "Utility/Graphic.hh"

Item::Item(Theme *theme, Alignment align, float scale) :
  _focused(false),
  _pressed(false),
  _release(false),
  _theme(theme),
  _align(align),
  _scale(scale),
  _border_type(Border::None)
{
}

Item::~Item()
{
}

Theme			*Item::getTheme()
{
  return (_theme);
}

void			Item::pressed()
{
  _pressed = true;
  if (_callback)
    _callback();
}

void			Item::released()
{
  _pressed = false;
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

bool			Item::textEntered(const std::string &)
{
  return (false);
}

void			Item::mouseCaught(int, int)
{
  if (!_focused)
  {
    _focused = true;
    designChanged();
  }
}

void			Item::mouseLeft()
{
  _focused = false;
  designChanged();
}

void			Item::setTheme(Theme *theme)
{
  _theme = theme;
}

Rect			Item::getRect() const
{
  Rect			rsrc = getRectRessource();

  rsrc.width += _margin.x * 2;
  rsrc.height += _margin.y * 2;
  rsrc.left -= _margin.x;
  rsrc.top -= _margin.y;

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
  _rec = rec;

  _box.setSize(sf::Vector2f(_rec.width, _rec.height));
  _box.setPosition(sf::Vector2f(_rec.left, _rec.top));
}

void			Item::addCallback(Callback callback)
{
  _callback = callback;
}

void			Item::removeCallback()
{
  _callback = nullptr;
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
  pos.y += _margin.y;

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
