#include "Input.hh"

Input::Input(Theme *theme, float scale) :
  Item(theme, scale),
  _thickness(THICKNESS),
  _cursor_pos(0),
  _cursor_selection(-1),
  _max_length(999)
{
  _input.setOutlineThickness(THICKNESS);
}

Input::~Input()
{
}

void			Input::draw(sf::RenderWindow &win)
{
  Item::draw(win);

  win.draw(_input);

  Screen::scissor(Rect(_rec.left + PADDING_TEXT, _rec.top, _rec.width - PADDING_TEXT, _rec.height));
  win.draw(_text);

  // Only draw when pressed
  if (_pressed)
  {
    // Draw selection or cursor
    if (_cursor_selection != -1)
      win.draw(_selection);
    else
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
  Screen::undoScissor();
}

void			Input::designChanged()
{
  Item::designChanged();

  _text.setFont(_theme->f_text);
  _text.setCharacterSize(_theme->size_text);
  _cursor.setFillColor(_theme->c_border_pressed);
  _selection.setFillColor(_theme->c_border * sf::Color(1, 1, 1, 64));

  if (!_release && _pressed)
  {
    _input.setFillColor(_theme->c_background_pressed);
    _input.setOutlineColor(_theme->c_border_pressed);
    _text.setColor(_theme->c_text_pressed);
  }
  else if (_focused)
  {
    _input.setFillColor(_theme->c_background_focused);
    _input.setOutlineColor(_theme->c_border_focused);
    _text.setColor(_theme->c_text_focused);
  }
  else
  {
    _input.setFillColor(_theme->c_background);
    _input.setOutlineColor(_theme->c_border);
    _text.setColor(_theme->c_text);
  }
}

void			Input::update()
{
  sf::Vector2i		pos = getRessourcePosition();
  _input.setPosition(pos.x, pos.y);
  _text.setPosition(pos.x + PADDING_TEXT, pos.y);

  designChanged();

  updateRendering();
}

void			Input::updateRendering()
{
  int	width_text = _text.getLocalBounds().width;
  int	x_diff = 0;

  // Text displayed is out of input
  if (width_text >= _rec.width - PADDING_TEXT)
  {
    x_diff = _text.findCharacterPos(_cursor_pos).x - _text.findCharacterPos(0).x;

    if (x_diff >= _rec.width - PADDING_TEXT - _thickness * 2)
      x_diff = (_rec.width - PADDING_TEXT * 2) - x_diff;
    else
      x_diff = 0;
  }

  _text.setPosition(_rec.left + PADDING_TEXT + x_diff, _rec.top +
      ((_rec.height - _text.getCharacterSize() - 2) / 2));

  updateCursor();
}

Rect			Input::getRectRessource() const
{
  return (_rec);
}

void			Input::setInput(const std::string &text)
{
  _string = text;
  _text.setString(text);
  _cursor_pos = text.size();
}

const std::string	&Input::getInput()
{
  return (_string);
}

int			Input::getThickness() const
{
  return (_thickness);
}

void			Input::setThickness(int thickness)
{
  _thickness = thickness;
  _input.setOutlineThickness(_thickness);
}

void			Input::mouseReleased(int x, int y)
{
  // Check if not already pressed
  if (_pressed)
    return ;

  Item::mouseReleased(x, y);

  // Add all callback for an input
  using namespace std::placeholders;
  catchEvent(Action(sf::Event::TextEntered), std::bind(&Input::textEntered, this, _1));
  catchEvent(Action(sf::Event::MouseButtonPressed, sf::Mouse::Left), std::bind(&Input::click, this, _1));
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Return), std::bind(&Input::enterPressed, this, _1));
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Left), std::bind(&Input::goLeft, this, _1));
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Right), std::bind(&Input::goRight, this, _1));
  // Special input
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::A), std::bind(&Input::selectAll, this, _1));
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Delete), std::bind(&Input::removeFront, this, _1));
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::BackSpace), std::bind(&Input::removeBack, this, _1));

  // Cursor at the end of the string
  _cursor_pos = _text.getString().getSize();
  updateCursor();
}

void			Input::updateCursor()
{
  sf::Vector2f cur_pos = _text.findCharacterPos(_cursor_pos);
  _cursor.setPosition(cur_pos.x, _input.getGlobalBounds().top + PADDING_CURSOR + _thickness);

  // Reset timer - Show visible because we update it
  _draw_cursor = true;
  _cursor_blink.restart();

  // Update selection if exist
  if (_cursor_selection != -1)
  {
    sf::Vector2f selection_pos = _text.findCharacterPos(_cursor_selection);

    int start_x = std::min(selection_pos.x, cur_pos.x);
    _selection.setPosition(start_x, _input.getGlobalBounds().top + PADDING_CURSOR + _thickness);

    // Checking selection out of input
    int width = std::abs(selection_pos.x - cur_pos.x);

    _selection.setSize(sf::Vector2f(width, _rec.height - PADDING_CURSOR * 2));
  }
}

void			Input::enterPressed(Context)
{
  released();
}

void			Input::released()
{
  Item::released();

  clearCallbacks();
}

void			Input::removeSelection()
{
  int	min_pos = std::min(_cursor_pos, _cursor_selection);

  _string.erase(min_pos, std::abs(_cursor_selection - _cursor_pos));
  _text.setString(_string);

  _cursor_pos = min_pos;
  _cursor_selection = -1;
}

void			Input::textEntered(Context context)
{
  std::string	str = "";
  sf::Utf<32>::encodeAnsi(context.text.unicode, std::back_inserter(str), '?');

  if (_string.length() + str.length() > (unsigned) _max_length)
    return ;

  // Check printable characters
  if (std::all_of(str.begin(), str.end(), isprint))
  {
    // Check selection : erase it
    if (_cursor_selection != -1)
      removeSelection();

    _string.insert(_cursor_pos, str);
    _text.setString(_string);
    _cursor_pos += str.length();

    updateRendering();
  }
}

bool			Input::isShiftPressed()
{
  return (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));
}

void			Input::checkSelection()
{
  // Check shift if selection then keep cursor pos
  if (isShiftPressed())
  {
    if (_cursor_selection == -1)
      _cursor_selection = _cursor_pos;
  }
  else
    _cursor_selection = -1;
}


//
// Callback functions
//

void			Input::click(Context context)
{
  if (!getRect().contains(sf::Vector2i(context.mouseButton.x, context.mouseButton.y)))
    released();
}

void			Input::goLeft(Context)
{
  checkSelection();

  // Check out of text
  if (_cursor_pos != 0)
    --_cursor_pos;

  updateRendering();
}

void			Input::goRight(Context)
{
  checkSelection();

  // Check out of text
  if (_cursor_pos < (int) _string.size())
    ++_cursor_pos;

  updateRendering();
}

void			Input::selectAll(Context)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
  {
    _cursor_pos = 0;
    _cursor_selection = _string.size();

    updateRendering();
  }
}

void			Input::removeFront(Context)
{
  if (_cursor_selection != -1)
    removeSelection();
  else if ((unsigned) _cursor_pos < _string.length())
  {
    _string.erase(_cursor_pos, 1);
    _text.setString(_string);
  }

  updateRendering();
}

void			Input::removeBack(Context)
{
  if (_cursor_selection != -1)
    removeSelection();
  else if ((unsigned) _cursor_pos > 0)
  {
    _string.erase(_cursor_pos - 1, 1);
    _text.setString(_string);

    --_cursor_pos;
  }

  updateRendering();
}

void			Input::setRect(const Rect &rec)
{
  Item::setRect(rec);

  _input.setSize(sf::Vector2f(_rec.width, _rec.height));
  _cursor.setSize(sf::Vector2f(1, _rec.height - PADDING_CURSOR * 2));
}

void			Input::setMaxLength(int length)
{
  _max_length = length;
}
