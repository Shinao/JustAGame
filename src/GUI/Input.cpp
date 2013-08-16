#include "GUI/Input.hh"

Input::Input(Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale)
{
}

Input::~Input()
{
}

void			Input::draw(sf::RenderWindow &win)
{
  Item::draw(win);
}

void			Input::designChanged()
{
  Item::designChanged();

  if (!_release && _pressed)
  {
  }
  else if (_focused)
  {
  }
  else
  {
  }
}

void			Input::update()
{
  _input.setPosition(_rec.left, _rec.top);

  designChanged();
}

Rect			Input::getRectRessource() const
{
}

// Overriding setRect to reset position of the ressource
void			Input::setRect(const Rect &rec)
{
  Item::setRect(rec);

  update();
}

void			Input::setInput(const sf::String &text)
{

  update();
}

const sf::String	&Input::getInput()
{
}

