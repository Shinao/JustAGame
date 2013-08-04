#include "GUI/Text.hh"

Text::Text(int id, const sf::String &text, Theme *theme, Alignment align, float scale)
  : Item(id, theme, align, scale)
{
  _text.setString(text);
}

Text::~Text()
{
}

void			Text::draw(sf::RenderWindow &win)
{
  Item::draw(win);
  win.draw(_text);
}

void			Text::mouseCaught(int x, int y)
{
  Item::mouseCaught(x, y);
  _text.setFont(_theme->f_text_focused);
  _text.setCharacterSize(_theme->size_text_focused);
  _text.setColor(_theme->c_text_focused);
  _text.setStyle(_theme->style_text_focused);
}

void			Text::mouseLeft()
{
  Item::mouseLeft();
  _text.setFont(_theme->f_text);
  _text.setCharacterSize(_theme->size_text);
  _text.setColor(_theme->c_text);
  _text.setStyle(_theme->style_text);
}

void			Text::update()
{
  _text.setScale(sf::Vector2f(_scale, _scale));

  sf::Vector2i		pos = getRessourcePosition();
  _text.setPosition(pos.x, pos.y);
}

Rect			Text::getRectRessource() const
{
  return (Rect(_text.getGlobalBounds()));
}

// Overriding setRect to reset position of the ressource
void			Text::setRect(const Rect &rec)
{
  Item::setRect(rec);

  update();
}

void			Text::setText(const sf::String &text)
{
  _text.setString(text);

  update();
}

const sf::String	&Text::getText()
{
  return (_text.getString());
}
