#include "GUI/Input.hh"

Input::Input(Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale),
  _size(sf::Vector2f(INPUT_WIDTH, INPUT_HEIGHT)),
  _thickness(INPUT_THICKNESS)
{
  _input.setSize(sf::Vector2f(_size));
  _input.setOutlineThickness(INPUT_THICKNESS);
}

Input::~Input()
{
}

void			Input::draw(sf::RenderWindow &win)
{
  Item::draw(win);

  win.draw(_input);
  win.draw(_text);
}

void			Input::designChanged()
{
  Item::designChanged();

  _text.setFont(_theme->f_text);
  _text.setCharacterSize(_theme->size_text);
  _text.setColor(_theme->c_text);
  _text.setStyle(_theme->style_text);

  if (!_release && _pressed)
  {
    _input.setFillColor(_theme->c_border_pressed);
  }
  else if (_focused)
  {
    _input.setFillColor(_theme->c_border_focused);
  }
  else
  {
    _input.setFillColor(_theme->c_border);
  }
  _input.setOutlineColor(_input.getFillColor() + sf::Color(16, 16, 16));
}

void			Input::update()
{
  sf::Vector2i		pos = getRessourcePosition();
  _input.setPosition(pos.x, pos.y);

  designChanged();
}

Rect			Input::getRectRessource() const
{
  Rect	rec = _rec;
  rec.width = INPUT_WIDTH;
  rec.height = INPUT_HEIGHT;

  return (rec);
}

// Overriding setRect to reset position of the ressource
void			Input::setRect(const Rect &rec)
{
  Item::setRect(rec);

  update();
}

void			Input::setInput(const sf::String &text)
{
  _text.setString(text);
}

const sf::String	&Input::getInput()
{
  return (_text.getString());
}

