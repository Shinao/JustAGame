#include <SFML/System.hpp>
#include "jag.hh"
#include "GUI/Screen.hh"

namespace Screen
{

  //
  // Private methods
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
	_map.pushEvent(event);

      // All event pushed - time to callback
      _map.invokeCallbacks(_system, &_window);
      _map.clearEvents();
    }

    void			manageClick(Context context)
    {
      int			x = context.event->mouseMove.x, y = context.event->mouseMove.y;

      if (_layer_focused != NULL && _layer_focused->getRect().contains(x, y))
	_layer_focused->clicked(x, y);
    }

    void			manageInput(Context context)
    {
      const sf::Event		&event = *(context.event);

      std::string str = "";
      sf::Utf<32>::encodeAnsi(event.text.unicode, std::back_inserter(str), '?');

      for (int i = _layers.size() - 1; i >= 0; --i)
	if (_layers[i]->textEntered(str))
	  return ;
    }

    void			manageMouse(Context context)
    {
      int			x = context.event->mouseMove.x, y = context.event->mouseMove.y;

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

    // Init to NULL
    for (auto layer : _layers)
      layer = NULL;

    // Recreate the window
    _window.create(sf::VideoMode(jag::windowWidth, jag::windowHeight), "JustAGame", sf::Style::None);
    _window.setKeyRepeatEnabled(false);

    _layer_focused = NULL;
    _action_id = 0;

    // Add special event callback
    addCallback(thor::Action(sf::Event::Closed), &close);
    addCallback(thor::Action(sf::Mouse::Left, thor::Action::PressOnce), &manageClick);
    addCallback(thor::Action(sf::Event::TextEntered), &manageInput);
    addCallback(thor::Action(sf::Event::MouseMoved), &manageMouse);
  }

  void			clear()
  {
    // Delete each layers
    for (auto layer : _layers)
      delete layer;

    _layers.clear();
    _map.clearActions();
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
	break ;
    }

    // Safety first - put your seat belt on please
    if (i == -1)
      i = 0;

    // Now we now which one is the main layer - calling the draw on each layer on the top
    for (; i < _layers.size(); ++i)
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

  // void			addCallback(const thor::Action &action, const std::function<void ()> &callback)
  // {
  //   int			id = _action_id++;

  //   _map[id] = action;
  //   _system.connect(id, std::bind(callback));
  // }

  void			addCallback(const thor::Action &action, const std::function<void (Context)> &callback)
  {
    int			id = _action_id++;

    _map[id] = action;
    _system.connect(id, callback);
  }

  thor::ActionMap<int>			&getMap()
  {
    return (_map);
  }

  thor::ActionMap<int>::CallbackSystem	&getSystem()
  {
    return (_system);
  }

  int					actionId()
  {
    return (_action_id++);
  }

  sf::WindowHandle			getWindowHandle()
  {
    return (_window.getSystemHandle());
  }

  const sf::RenderWindow		&getWindow()
  {
    return (_window);
  }

  sf::Vector2u				getWindowSize()
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
}
