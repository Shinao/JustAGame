#include "GUI/Input.hh"

Input::Input(EventManager &event, Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale),
  EventCallback(event),
  _size(sf::Vector2f(INPUT_WIDTH, INPUT_HEIGHT)),
  _thickness(INPUT_THICKNESS)
{
  _text.setString("Hello");
  _input.setSize(sf::Vector2f(_size));
  _input.setOutlineThickness(INPUT_THICKNESS);
  _cursor.setSize(sf::Vector2f(1, INPUT_HEIGHT - 12));
}

Input::~Input()
{
}

void			Input::draw(sf::RenderWindow &win)
{
  Item::draw(win);

  win.draw(_input);
  win.draw(_text);

  // Only draw when pressed
  if (_pressed)
  {

    // Toggle cursor for blinking
    if (_cursor_blink.getElapsedTime().asMilliseconds() > CURSOR_BLINK_SPEED)
    {
      _draw_cursor = !_draw_cursor;
      _cursor_blink.restart();
    }

    if (_draw_cursor)
      win.draw(_cursor);
  }
}

void			Input::designChanged()
{
  Item::designChanged();

  _text.setFont(_theme->f_text);
  _text.setCharacterSize(_theme->size_text);
  _text.setColor(_theme->c_text);
  _text.setStyle(_theme->style_text);
  _cursor.setFillColor(_theme->c_border_pressed);

  if (!_release && _pressed)
  {
    _input.setFillColor(_theme->c_border);
  }
  else if (_focused)
  {
    _input.setFillColor(_theme->c_border);
  }
  else
  {
    _input.setFillColor(_theme->c_border);
  }
  _input.setOutlineColor(_theme->c_border_focused);
}

void			Input::update()
{
  sf::Vector2i		pos = getRessourcePosition();
  _input.setPosition(pos.x, pos.y);
  _cursor.setPosition(pos.x + 4, pos.y + 6);
  _text.setPosition(pos.x + PADDING_TEXT, pos.y + ((INPUT_HEIGHT -
	  (_text.getLocalBounds().height + _text.getLocalBounds().top)) / 2));

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

const sf::Vector2i	&Input::getSize() const
{
  return (_size);
}

void			Input::setSize(const sf::Vector2i &size)
{
  _size = size;
}

int			Input::getThickness() const
{
  return (_thickness);
}

void			Input::setThickness(int thickness)
{
  _thickness = thickness;
}

#include <iostream>

void			Input::pressed()
{
  Item::pressed();

  // Add all callback for an input
  using namespace std::placeholders;

  catchEvent(Action(sf::Event::TextEntered), std::bind(&Input::textEntered, this, _1));
  catchEvent(Action(sf::Event::MouseButtonPressed, sf::Mouse::Left), std::bind(&Input::clickCallback, this, _1));
}

void			Input::released()
{
  Item::released();

  clearCallbacks();
}

void			Input::textEntered(Context &context)
{
  std::string	str = "";
  sf::Utf<32>::encodeAnsi(context.text.unicode, std::back_inserter(str), '?');

  _text.setString(_text.getString() + str);
}


// Callback

void			Input::clickCallback(Context context)
{
  if (!getRect().contains(sf::Vector2i(context.mouseButton.x, context.mouseButton.y)))
    released();
}
