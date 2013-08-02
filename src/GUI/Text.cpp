#include "GUI/Text.hh"

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
  _text.setFont(_theme->f_text_focused);
  _text.setCharacterSize(_theme->size_text_focused);
  _text.setColor(_theme->c_text_focused);
  _text.setStyle(_theme->style_text_focused);
}

void			Text::mouseLeft()
{
  _text.setFont(_theme->f_text);
  _text.setCharacterSize(_theme->size_text);
  _text.setColor(_theme->c_text);
  _text.setStyle(_theme->style_text);
}

void			Text::update()
{
  _text.setScale(sf::Vector2f(_scale, _scale));

  // Getting width & height depending on text
  auto			rec = _text.getGlobalBounds(); 
  _rec.width = rec.width;
  _rec.height = rec.height;

  // Getting x depending on alignment
  int x = _rec.left;
  x += _margin;
  if (_align == Center)
    x += rec.width / 2 + _margin;
  else
    x += rec.width + _margin;
  _text.setPosition(x, _rec.top);
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
