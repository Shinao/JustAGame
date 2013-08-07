#include <SFML/System.hpp>
#include "jag.hh"
#include "GUI/Screen.hh"

namespace Screen
{

  //
  // Private attributes - methods
  // Declaration
  //

  namespace
  {
    const sf::Color		BACKGROUND_CLEAR = sf::Color::White;
    const unsigned		MAX_LAYERS_EXPECTED = 100;
    std::vector<Layer *>	_layers;
    sf::RenderWindow		_window;
    Layer			*_layer_focused;
    sf::Clock			_timer;
    EventManager		_event_manager;

    unsigned			getNextId();
    void			checkEvent();
    void			updateFocused();

    // Event catched
    void			clicked(Context context);
    void			mouseMoved(Context context);
    void			textEntered(Context context);
    void			mouseLeft(Context context);
  }

  //
  // Definition
  //

  namespace
  {
    unsigned			getNextId()
    {
      // Check not enough space : double capacity
      if (_layers.size() >= _layers.capacity())
	_layers.reserve(_layers.capacity() + MAX_LAYERS_EXPECTED);

      return (_layers.size());
    }

    void			checkEvent()
    {
      sf::Event			event;

      // Everything is done by callbacks - thanks C++11
      while (_window.pollEvent(event))
	_event_manager.push(event);

      // All event pushed - time to callback
      _event_manager.invokeCallbacks();
    }

    void			clicked(Context context)
    {
      int			x = context.mouseMove.x, y = context.mouseMove.y;

      if (_layer_focused != NULL && _layer_focused->getRect().contains(x, y))
	_layer_focused->clicked(x, y);
    }

    void			mouseLeft(Context)
    {
      if (_layer_focused != NULL)
	_layer_focused->mouseLeft();
    }

    void			textEntered(Context context)
    {
      std::string str = "";
      sf::Utf<32>::encodeAnsi(context.text.unicode, std::back_inserter(str), '?');

      for (int i = _layers.size() - 1; i >= 0; --i)
	if (_layers[i]->textEntered(str))
	  return ;
    }

    void			mouseMoved(Context context)
    {
      int			x = context.mouseMove.x, y = context.mouseMove.y;

      // If we have a layer focused
      if (_layer_focused != NULL)
      {
	// Check if still on the same layer to avoid unnecessary check
	if (_layer_focused->getRect().contains(x, y))
	{
	  _layer_focused->mouseCaught(x, y);
	  return ;
	}

	// No ? Tell it lost focus
	_layer_focused->mouseLeft();
      }

      // Get the new focus and call it
      updateFocused();
      if (_layer_focused != NULL)
	_layer_focused->mouseCaught(x, y);
    }

    void			updateFocused()
    {
      sf::Vector2i		cur = sf::Mouse::getPosition(_window);
      Layer			*ly;

      for (int i = _layers.size() - 1; i >= 0; --i)
      {
	ly = _layers[i];
	if (ly->catchMouse() && ly->getRect().contains(cur.x, cur.y))
	{
	  _layer_focused = _layers[i];
	  return ;
	}
      }

      _layer_focused = NULL;
    }
  }



  //
  // Public methods
  //

  void			init()
  {
    // Get enough space if possible
    if (_layers.capacity() < MAX_LAYERS_EXPECTED)
      _layers.reserve(MAX_LAYERS_EXPECTED);

    // Recreate the window
    _window.create(sf::VideoMode(jag::windowWidth, jag::windowHeight), "JustAGame", sf::Style::None);
    _window.setKeyRepeatEnabled(false);

    _layer_focused = NULL;

    // Add special event callback
    _event_manager.add(Action(sf::Event::Closed), &close);
    _event_manager.add(Action(sf::Event::MouseButtonReleased, sf::Mouse::Left), &clicked);
    _event_manager.add(Action(sf::Event::TextEntered), &textEntered);
    _event_manager.add(Action(sf::Event::MouseMoved), &mouseMoved);
    _event_manager.add(Action(sf::Event::MouseLeft), &mouseLeft);
  }

  void			clear()
  {
    // Delete each layers
    for (auto layer : _layers)
      delete layer;

    _layers.clear();
    _event_manager.clear();
    _layer_focused = NULL;
  }

  void			update()
  {
    int			i;

    _window.clear(BACKGROUND_CLEAR);

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
  }

  void			add(Layer *layer)
  {
    unsigned		id = getNextId();

    _layers.push_back(layer);
    layer->setId(id);
    updateFocused();
  }

  void			remove(Layer *layer)
  {
    // Moving all the layer from one index down
    for (unsigned i = layer->getId(); i + 1 < _layers.size(); ++i)
      _layers[i] = _layers[i + 1];

    _layers.pop_back();
    delete layer;
    updateFocused();
  }

  sf::WindowHandle			getHandle()
  {
    return (_window.getSystemHandle());
  }

  const sf::RenderWindow		&getWindow()
  {
    return (_window);
  }

  sf::Vector2u				getSize()
  {
    return (_window.getSize());
  }

  sf::Vector2i				getCursorPosition()
  {
    return (sf::Mouse::getPosition(_window));
  }

  void					close(Context)
  {
    _window.close();
  }

  bool					isActive()
  {
    return (_window.isOpen());
  }

  EventManager				&getEventManager()
  {
    return (_event_manager);
  }
}
