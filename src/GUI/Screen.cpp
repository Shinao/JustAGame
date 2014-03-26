#include <SFML/System.hpp>
#include "GUI/Screen.hh"
#include "jag.hh"
#include "OSSpecific.hh"


// Static declaration
bool 				Screen::_moving = false;
sf::Vector2i			Screen::_old_cursor_pos;
sf::Vector2i			Screen::_pressed_pos;
sf::RenderWindow		Screen::_window;


Screen::Screen(Mode mode) :
  _layer_focused(NULL)
{
  // Get enough space
  _layers.reserve(MAX_LAYERS_EXPECTED);

  // Recreate the window depending on the mode
  if (mode == Setting)
  {
    _window.create(sf::VideoMode(jag::WindowWidth, jag::WindowHeight), jag::WindowName, sf::Style::None);
    _window.setKeyRepeatEnabled(false);
    restore();
  }

  // Add special event callback
  using namespace std::placeholders;

  _event_manager.add(Action(sf::Event::Closed), std::bind(&Screen::close, _1));
  _event_manager.add(Action(sf::Event::MouseButtonPressed, sf::Mouse::Left), std::bind(&Screen::pressed, this, _1));
  _event_manager.add(Action(sf::Event::MouseButtonReleased, sf::Mouse::Left), std::bind(&Screen::released, this, _1));
  _event_manager.add(Action(sf::Event::MouseMoved), std::bind(&Screen::mouseMoved, this, _1));
  _event_manager.add(Action(sf::Event::MouseLeft), std::bind(&Screen::mouseLeft, this, _1));
  _event_manager.add(Action(sf::Event::LostFocus), std::bind(&Screen::mouseLeft, this, _1));
}

Screen::~Screen()
{
  for (auto layer : _layers)
    delete layer;
}



// 
// Private 
// 

unsigned			Screen::getNextId()
{
  // Check not enough space : double capacity
  if (_layers.size() >= _layers.capacity())
    _layers.reserve(_layers.capacity() + MAX_LAYERS_EXPECTED);

  return (_layers.size());
}

void				Screen::checkEvent()
{
  sf::Event			event;

  // Check if user wants to move the window
  manageMoving();

  // Everything is done by callbacks - thanks C++11
  while (_window.pollEvent(event))
    _event_manager.push(event);

  // All event pushed - time to callback
  _event_manager.invokeCallbacks();
}

void				Screen::pressed(Context context)
{
  int	x = context.mouseButton.x, y = context.mouseButton.y;

  if (_layer_focused != NULL)
    _layer_focused->pressed(x, y);
}

void				Screen::released(Context context)
{
  int	x = context.mouseButton.x, y = context.mouseButton.y;

  if (_layer_focused != NULL)
    _layer_focused->released(x, y);
}

void				Screen::manageMoving()
{
  if (_moving)
  {
    // Get the new position of the cursor
    sf::Vector2i cursor_pos = sf::Mouse::getPosition();

    // Move the window depending on where we were when pressed
    // Only if the position of the cursor has changed
    if (cursor_pos != _old_cursor_pos)
    {
      _window.setPosition(cursor_pos - _pressed_pos);
      _old_cursor_pos = cursor_pos;
    }
  }
}

void				Screen::mouseMoved(Context context)
{
  int	x = context.mouseMove.x, y = context.mouseMove.y;

  // Get the new focus
  updateFocused();

  if (_layer_focused != NULL)
    _layer_focused->mouseCaught(x, y);
}

void				Screen::updateFocused()
{
  sf::Vector2i	cur = sf::Mouse::getPosition(_window);
  Layer		*ly;

  for (int i = _layers.size() - 1; i >= 0; --i)
  {
    ly = _layers[i];
    if (ly->catchMouse() && ly->getRect().contains(cur.x, cur.y))
    {
      // Check if layer lost focused
      if (_layer_focused != NULL && _layer_focused != _layers[i])
	_layer_focused->mouseLeft();

      // Update focused
      _layer_focused = _layers[i];
      return ;
    }
  }

  _layer_focused = NULL;
}

void				Screen::manageLayers()
{
  if (_layers_to_remove.size() > 0)
  {
    for (auto layer : _layers_to_remove)
    {
      // Moving all the layer from one index down
      for (unsigned i = layer->getId(); i + 1 < _layers.size(); ++i)
	_layers[i] = _layers[i + 1];

      _layers.pop_back();
      delete layer;
    }

    _layers_to_remove.clear();

    // Update focused in case we deleted it
    updateFocused();
  }
}




// 
// Public 
// 

void				Screen::update()
{
  int			i;

  checkEvent();

  // Start from the end
  for (i = _layers.size() - 1; i >= 0; --i)
  {
    // Check if layer wants to be the last updated
    if (!_layers[i]->update(_window))
    {
      --i;
      break ;
    }
  }

  // Safety first - put your seat belt on please
  ++i;

  // Now we now which one is the main layer - calling the draw on each layer on the top
  for (; (unsigned) i < _layers.size(); ++i)
    _layers[i]->draw(_window);

  // Waiting FPS frames
  while (_timer.getElapsedTime().asMilliseconds() < jag::FPS);
  _timer.restart();

  _window.display();

  // Safely remove layers if asked and things
  manageLayers();
}

void				Screen::add(Layer *layer)
{
  unsigned		id = getNextId();

  _layers.push_back(layer);
  layer->setId(id);
  updateFocused();
}

void				Screen::remove(Layer *layer)
{
  _layers_to_remove.push_back(layer);
}

sf::WindowHandle			Screen::getHandle()
{
  return (_window.getSystemHandle());
}

const sf::RenderWindow			&Screen::getWindow()
{
  return (_window);
}

sf::Vector2u				Screen::getSize()
{
  return (_window.getSize());
}

sf::Vector2i				Screen::getCursorPosition()
{
  return (sf::Mouse::getPosition(_window));
}

void					Screen::close(Context)
{
  closeWindow();
}

void					Screen::closeWindow()
{
  _window.close();
}

bool					Screen::isActive()
{
  return (_window.isOpen());
}

EventManager				&Screen::getEventManager()
{
  return (_event_manager);
}

void					Screen::minimize()
{
  minimizeImpl(_window.getSystemHandle());
}

void					Screen::setCursor(CursorType type)
{
  setCursorImpl(_window.getSystemHandle(), type);
}

void					Screen::openUrl(const std::string &url)
{
  openUrlImpl(url);
}

void						Screen::restore()
{
  sf::VideoMode	screen = sf::VideoMode::getDesktopMode();

  _window.setPosition(sf::Vector2i(screen.width / 2 - jag::WindowWidth / 2,
	screen.height / 2 - jag::WindowHeight / 2));
}

void					Screen::setMoving(bool moving)
{
  _moving = moving;

  if (_moving)
    _pressed_pos = sf::Mouse::getPosition() - _window.getPosition();
}

void					Screen::mouseLeft(Context)
{
  if (_moving)
    manageMoving();
  else
  {
    if (_layer_focused != NULL)
      _layer_focused->mouseLeft();
  }
}
