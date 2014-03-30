#include "GUI/String.hh"

String::String(const sf::String &text, Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale)
{
  _text.setString(text);

  // Set font & CharacterSize
  designChanged();
}

String::~String()
{
}

void			String::draw(sf::RenderWindow &win)
{
  Item::draw(win);
  win.draw(_text);
}

void			String::designChanged()
{
  Item::designChanged();

  if (_pressed)
  {
    _text.setFont(_theme->f_text_pressed);
    _text.setCharacterSize(_theme->size_text_pressed);
    _text.setColor(_theme->c_text_pressed);
    _text.setStyle(_theme->style_text_pressed);
  }
  else if (_focused)
  {
    _text.setFont(_theme->f_text_focused);
    _text.setCharacterSize(_theme->size_text_focused);
    _text.setColor(_theme->c_text_focused);
    _text.setStyle(_theme->style_text_focused);
  }
  else
  {
    _text.setFont(_theme->f_text);
    _text.setCharacterSize(_theme->size_text);
    _text.setColor(_theme->c_text);
    _text.setStyle(_theme->style_text);
  }
}

void			String::update()
{
  _text.setScale(sf::Vector2f(_scale, _scale));

  sf::Vector2i		pos = getRessourcePosition();
  _text.setPosition(pos.x - _text.getLocalBounds().left, pos.y - _text.getLocalBounds().top / 2);

  designChanged();
}

Rect			String::getRectRessource() const
{
  return (Rect(_text.getLocalBounds()));
}

void			String::setString(const sf::String &text)
{
  _text.setString(text);

  update();
}

const sf::String	&String::getString()
{
  return (_text.getString());
}
