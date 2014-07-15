#include "String.hh"
#include <iostream>

String::String(const sf::String &text, Theme *theme, float scale) :
  Item(theme, scale)
{
  setString(text);
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
  // Reset text
  _text.setString(_text_original);

  // Check out of bounds
  std::string	str = _text_original;
  bool		formatted = false;

  while (_text.getLocalBounds().width + _margin.x > _rec.width && str != "")
  {
    formatted = true;
    str.erase(str.size() - 1, 1);
    _text.setString(str);
  }

  if (formatted)
  {
    for (int i = 1; i < 4; ++i)
      str[str.size() - i] = '.';
    _text.setString(str);
  }

  _text.setScale(sf::Vector2f(_scale, _scale));

  sf::Vector2i pos = getRessourcePosition();
  _text.setPosition(pos.x, pos.y);

  designChanged();
}

Rect			String::getRectRessource() const
{
  Rect rec = Rect(_text.getLocalBounds());

  // Manage multi-lines \n
  if (_text.getFont() != NULL)
  {
    rec.height += rec.top;
    unsigned mod = rec.height % _text.getCharacterSize();
    if (mod < _text.getCharacterSize() / 2)
      rec.height -= mod;
  }

  return (rec);
}

void			String::setRect(const Rect &rec)
{
  Item::setRect(rec);
}

void			String::setString(const std::string &text)
{
  _text_original = text;
  _text.setString(text);

  update();
}

const sf::String	&String::getString()
{
  return (_text.getString());
}
