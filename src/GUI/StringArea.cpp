#include "StringArea.hh"
#include <iostream>

StringArea::StringArea(const sf::String &str, Theme *theme) :
  Item(theme),
  _string(str)
{
}

StringArea::~StringArea()
{
  for (auto text : _texts)
    delete text;
}

void			StringArea::setString(const sf::String &str)
{
  _string = str;
  updateRendering();
}

void			StringArea::updateRendering()
{
  for (auto text : _texts)
    delete text;
  _texts.clear();

  unsigned	y = 0;
  unsigned	pos;

  sf::Text	rendu(_string, _theme->f_text, _theme->size_text);
  sf::String	str = _string;

  sf::Vector2i	rsrc_pos = getRessourcePosition();

  while (str.getSize() > 0)
  {
    pos = 0;

    while (pos < str.getSize() && rendu.findCharacterPos(pos).x + rendu.getCharacterSize() <= _rec.width)
      ++pos;

    sf::String formatted_str = str;
    formatted_str.erase(pos, str.getSize() - pos);

    sf::Text *formatted = new sf::Text(formatted_str, _theme->f_text, _theme->size_text);
    formatted->setPosition(rsrc_pos.x, _rec.top + y + _margin.y);

    y += formatted->getCharacterSize() + LINE_HEIGHT;
    if ((int) (y + _rec.top + rendu.getCharacterSize()) > _rec.top + _rec.height)
    {
      sf::String new_str = formatted->getString();
      for (int i = 1; i < 4; ++i)
	new_str[new_str.getSize() - i] = '.';
      formatted->setString(new_str);
      _texts.push_back(formatted);
      break ;
    }
    _texts.push_back(formatted);

    str.erase(0, pos);
    if (str[0] == ' ')
      str.erase(0, 1);

    rendu.setString(str);
  }
}

void			StringArea::draw(sf::RenderWindow &win)
{
  Item::draw(win);

  for (auto text : _texts)
    win.draw(*text);
}

void			StringArea::designChanged()
{
  Item::designChanged();

  if (_pressed)
    for (auto text : _texts)
    {
      text->setFont(_theme->f_text_pressed);
      text->setCharacterSize(_theme->size_text_pressed);
      text->setColor(_theme->c_text_pressed);
      text->setStyle(_theme->style_text_pressed);
    }
  else if (_focused)
    for (auto text : _texts)
    {
      text->setFont(_theme->f_text_focused);
      text->setCharacterSize(_theme->size_text_focused);
      text->setColor(_theme->c_text_focused);
      text->setStyle(_theme->style_text_focused);
    }
  else
    for (auto text : _texts)
    {
      text->setFont(_theme->f_text);
      text->setCharacterSize(_theme->size_text);
      text->setColor(_theme->c_text);
      text->setStyle(_theme->style_text);
    }
}

void			StringArea::update()
{
  updateRendering();
  designChanged();
}

void			StringArea::setRect(const Rect &rec)
{
  Item::setRect(rec);
}

Rect			StringArea::getRectRessource() const
{
  int	y = 0;

  for (auto text : _texts)
    y += text->getCharacterSize() + LINE_HEIGHT;

  Rect rec = _rec;
  rec.height = y;
  return (rec);
}
