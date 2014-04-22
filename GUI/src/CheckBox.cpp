#include "CheckBox.hh"
#include <iostream>

CheckBox::CheckBox(String *string, Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale),
  _string(string)
{
  // Init check box
  _border.setSize(sf::Vector2f(CHECKBOX_SIZE, CHECKBOX_SIZE));
  _border.setFillColor(sf::Color::Transparent);
  _border.setOutlineThickness(1);

  _check.setSize(sf::Vector2f(CHECKBOX_SIZE - CHECKBOX_SPACE * 2, CHECKBOX_SIZE - CHECKBOX_SPACE * 2));
}

CheckBox::~CheckBox()
{
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

  rec.width = _string->getRect().width + CHECKBOX_SIZE + CHECKBOX_PADDING * 2;
  return (rec);
}

void			CheckBox::setRect(const Rect &rec)
{
  Item::setRect(rec);

  Rect srec = rec;
  srec.left += CHECKBOX_SIZE + CHECKBOX_PADDING * 2;
  srec.width -= CHECKBOX_SIZE - CHECKBOX_PADDING * 3;
  _string->setRect(srec);
  _border.setPosition(rec.left + CHECKBOX_PADDING, rec.top + rec.height / 2 - CHECKBOX_SIZE / 2 + 1);
  _check.setPosition(rec.left + CHECKBOX_PADDING + CHECKBOX_SPACE, rec.top + rec.height / 2 - CHECKBOX_SIZE / 2 + CHECKBOX_SPACE + 1);
}

void		CheckBox::update()
{
  designChanged();
}

void		CheckBox::mouseCaught(int x, int y)
{
  Item::mouseCaught(x, y);

  _string->mouseCaught(x, y);
}

void		CheckBox::mouseLeft()
{
  Item::mouseLeft();

  _string->mouseLeft();
}

void		CheckBox::mouseReleased(int x, int y)
{

  _string->mouseReleased(x, y);
  Item::mouseReleased(x, y);
  // Toggle checking
  _is_checked = !_is_checked;
}

