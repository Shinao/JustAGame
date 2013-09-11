#include "GUI/Input.hh"

Input::Input(EventManager &event, Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale),
  EventCallback(event),
  _size(sf::Vector2f(INPUT_WIDTH, INPUT_HEIGHT)),
  _thickness(INPUT_THICKNESS),
  _cursor_pos(0),
  _cursor_selection(-1)
{
  // setInput("Hello");
  _input.setSize(sf::Vector2f(_size));
  _input.setOutlineThickness(INPUT_THICKNESS);
  _cursor.setSize(sf::Vector2f(1, INPUT_HEIGHT - PADDING_CURSOR * 2));
  _render_texture.create(INPUT_WIDTH - INPUT_THICKNESS - 2, INPUT_HEIGHT);
}

Input::~Input()
{
}

void			Input::draw(sf::RenderWindow &win)
{
  Item::draw(win);

  win.draw(_input);
  win.draw(_render);

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
}

void			Input::designChanged()
{
  Item::designChanged();

  _text.setFont(_theme->f_text);
  _text.setCharacterSize(_theme->size_text);
  _text.setColor(_theme->c_text);
  _text.setStyle(_theme->style_text);
  _cursor.setFillColor(_theme->c_border_pressed);
  _selection.setFillColor(_theme->c_border * sf::Color(1, 1, 1, 64));

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
  _render.setPosition(pos.x + PADDING_TEXT, pos.y);

  designChanged();

  updateRendering();
}

void			Input::updateRendering()
{
  int	width_text = _text.getLocalBounds().width;
  int	x_diff = 0;

  // Text displayed is out of input
  if (width_text > INPUT_WIDTH)
  {
    x_diff = _text.findCharacterPos(_cursor_pos).x - _text.findCharacterPos(0).x;

    if (x_diff > INPUT_HEIGHT)
      x_diff = x_diff - INPUT_HEIGHT;
    else
      x_diff = 0;
  }

  _text.setPosition(x_diff, (INPUT_HEIGHT - _text.getLocalBounds().height - _text.getLocalBounds().top) / 2);
  _render_texture.clear(sf::Color::Transparent);
  _render_texture.draw(_text);
  _render_texture.display();
  _render.setTexture(_render_texture.getTexture());

  updateCursor();
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

void			Input::pressed()
{
  Item::pressed();

  // Add all callback for an input
  using namespace std::placeholders;
  catchEvent(Action(sf::Event::TextEntered), std::bind(&Input::textEntered, this, _1));
  catchEvent(Action(sf::Event::MouseButtonPressed, sf::Mouse::Left), std::bind(&Input::click, this, _1));
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
  sf::Vector2f cur_pos = _text.findCharacterPos(_cursor_pos) + _render.getPosition();
  _cursor.setPosition(cur_pos.x, _input.getGlobalBounds().top + PADDING_CURSOR + INPUT_THICKNESS);

  // Reset timer - Show visible because we update it
  _draw_cursor = true;
  _cursor_blink.restart();

  // Update selection if exist
  if (_cursor_selection != -1)
  {
    sf::Vector2f selection_pos = _text.findCharacterPos(_cursor_selection);

    int start_x = std::min(selection_pos.x, cur_pos.x);
    _selection.setPosition(start_x, cur_pos.y);
    _selection.setSize(sf::Vector2f(std::abs(selection_pos.x - cur_pos.x), INPUT_HEIGHT - 12));
  }
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

void			Input::textEntered(Context &context)
{
  std::string	str = "";
  sf::Utf<32>::encodeAnsi(context.text.unicode, std::back_inserter(str), '?');

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


// Callback function

void			Input::click(Context context)
{
  if (!getRect().contains(sf::Vector2i(context.mouseButton.x, context.mouseButton.y)))
    released();
}

void			Input::goLeft(Context)
{
  checkSelection();

  // Check out of text
  if (_cursor_pos == 0)
    return ;

  --_cursor_pos;

  updateRendering();
}

void			Input::goRight(Context)
{
  checkSelection();

  // Check out of text
  if (_cursor_pos >= (int) _string.size())
    return ;

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
