#include "GUI/Item.hh"

  Item::Item(Theme *theme, Alignment align, float scale)
: _theme(theme),
  _align(align),
  _scale(scale),
  _margin(0),
  _focused(false),
  _pressed(false)
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

void			Item::unPressed()
{
  _pressed = false;
}

void			Item::designChanged()
{
  if (_pressed)
  {
  }
  else if (_focused)
  {
    _box.setFillColor(_theme->c_background_focused);
  }
  else
  {
    _box.setFillColor(_theme->c_background);
  }
}

void			Item::draw(sf::RenderWindow &win)
{
  win.draw(_box);
}

bool			Item::textEntered(const std::string &)
{
  return (false);
}

void			Item::mouseCaught(int x, int y)
{
  _focused = true;
  designChanged();
}

void			Item::mouseLeft()
{
  _focused = false;
  designChanged();
}

void			Item::setTheme(Theme *theme)
{
  _theme = theme;
  designChanged();
}

Rect			Item::getRect() const
{
  Rect			rsrc = getRectRessource();

  rsrc.width += _margin * 2;
  rsrc.left -= _margin;
  rsrc.height = _rec.height;
  rsrc.top = _rec.top;
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
    pos.x += _margin;
  else if (_align == Center)
    pos.x += rsrc.width / 2 + _margin;
  else
    pos.x += rsrc.width + _margin;

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

int			Item::getMargin() const
{
  return (_margin);
}

void			Item::setMargin(int margin)
{
  _margin = margin;
}
