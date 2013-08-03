#include "GUI/Sprite.hh"

Sprite::Sprite(int id, Theme *theme, Alignment align, float scale)
  : Item(id, theme, align, scale)
{
}

Sprite::~Sprite()
{
}

void			Sprite::draw(sf::RenderWindow &win)
{
  Item::draw(win);
  win.draw(*_sprite);
}


void			Sprite::update()
{
  _sprite->setScale(sf::Vector2f(_scale, _scale));

  // Getting width & height depending on text
  auto			rec = _sprite->getGlobalBounds(); 
  _rec.width = rec.width;
  _rec.height = rec.height;

  // Getting x depending on alignment
  int x = _rec.left;
  x += _margin;
  if (_align == Center)
    x += rec.width / 2 + _margin;
  else
    x += rec.width + _margin;
  _sprite->setPosition(x, _rec.top);
}

// Overriding setRect to reset position of the ressource
void			Sprite::setRect(const Rect &rec)
{
  Item::setRect(rec);

  update();
}

void			Sprite::setSprite(sf::Sprite *sprite)
{
  _sprite = sprite;
  update();
}

sf::Sprite		*Sprite::getSprite()
{
  return (_sprite);
}

