#include "GUI/Sprite.hh"

Sprite::Sprite(sf::Sprite *sprite, Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale),
  _sprite(sprite)
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

  sf::Vector2i		pos = getRessourcePosition();
  _sprite->setPosition(pos.x, pos.y);

  designChanged();
}

Rect			Sprite::getRectRessource() const
{
  return (Rect(_sprite->getGlobalBounds()));
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
