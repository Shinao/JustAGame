#include "GUI/CheckBox.hh"
#include <iostream>

CheckBox::CheckBox(String *string, Theme *theme, float scale) :
  Item(theme, scale),
  _string(string),
  _is_checked(false)
{
  // Init check box
  _border.setSize(sf::Vector2f(SIZE, SIZE));
  _border.setFillColor(sf::Color::Transparent);
  _border.setOutlineThickness(1);

  _check.setSize(sf::Vector2f(SIZE - SPACE * 2, SIZE - SPACE * 2));
}

CheckBox::~CheckBox()
{
  delete _string;
}

bool			CheckBox::isChecked() const
{
  return (_is_checked);
}

void			CheckBox::draw(sf::RenderWindow &win)
{
  Item::draw(win);

  _string->draw(win);
  win.draw(_border);

  if (_is_checked)
    win.draw(_check);
}

void			CheckBox::designChanged()
{
  Item::designChanged();

  if (!_release && _pressed)
  {
    _border.setOutlineColor(_theme->c_border_pressed);
    _check.setFillColor(_theme->c_border_pressed);
  }
  else if (_focused)
  {
    _border.setOutlineColor(_theme->c_border_focused);
    _check.setFillColor(_theme->c_border_focused);
  }
  else
  {
    _border.setOutlineColor(_theme->c_border);
    _check.setFillColor(_theme->c_border);
  }
}

Rect			CheckBox::getRectRessource() const
{
  Rect rec = _rec;

  rec.width = _string->getRect().width + SIZE + PADDING * 2;
  return (rec);
}

void			CheckBox::setRect(const Rect &rec)
{
  Item::setRect(rec);
}

void			CheckBox::update()
{
  designChanged();

  Rect srec = _rec;
  srec.left += SIZE + PADDING * 2;
  srec.width -= SIZE - PADDING * 3;

  _string->setRect(srec);
  _border.setPosition(_rec.left + PADDING, _rec.top + _rec.height / 2 - SIZE / 2);
  _check.setPosition(_rec.left + PADDING + SPACE, _rec.top + _rec.height / 2 - SIZE / 2 + SPACE);
}

void			CheckBox::mouseCaught(int x, int y)
{
  Item::mouseCaught(x, y);

  _string->mouseCaught(x, y);
}

void			CheckBox::mouseLeft()
{
  Item::mouseLeft();

  _string->mouseLeft();
}

void			CheckBox::mouseReleased(int x, int y)
{
  Item::mouseReleased(x, y);
  _string->mouseReleased(x, y);

  // Toggle checking
  _is_checked = !_is_checked;
}

void			CheckBox::setChecked(bool checked)
{
  _is_checked = checked;
}
