#include "GUI/Item.hh"

Item::Item(int id, Theme *theme, Alignment align, float scale)
  : _theme(theme),
  _align(align),
  _scale(scale),
  _margin(0),
  _id(id),
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
  std::cout << "pressed" << std::endl;
}

void			Item::unPressed()
{
  _pressed = false;
  std::cout << "unpressed" << std::endl;
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
  _box.setFillColor(_theme->c_background_focused);
  std::cout << "mouuuuse" << std::endl;
}

void			Item::mouseLeft()
{
  _focused = false;
  _box.setFillColor(_theme->c_background);
  std::cout << "uuuunmouuuuse" << std::endl;
}

void			Item::setTheme(Theme *theme)
{
  _theme = theme;
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

void			Item::setId(int id)
{
  _id = id;
}

int			Item::getId() const
{
  return (_id);
}
