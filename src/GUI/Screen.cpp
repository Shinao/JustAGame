#include <SFML/System.hpp>
#include "Setting.hh"
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

      while (_window.pollEvent(event))
      {

	// Manage special event
	if (event.type == sf::Event::Closed)
	{
	  clear();
	  return ;
	}

	if (event.type == sf::Event::MouseMoved)
	  manageMouse(event.mouseMove.x, event.mouseMove.y);
	else if (event.type == sf::Event::TextEntered)
	  manageInput(event);
	else
	  _map.pushEvent(event);
      }

      // All event pushed - time to callback
      _map.invokeCallbacks(_system, NULL);
      _map.clearEvents();
    }

    void			manageInput(sf::Event &event)
    {
      for (int i = _layers.size() - 1; i >= 0; --i)
	if (_layers[i]->textEntered(event.text.unicode))
	  return ;
    }

    void			manageMouse(int x, int y)
    {
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
    _window.create(sf::VideoMode(Setting::windowWidth, Setting::windowHeight), "JustAGame", sf::Style::None);
    _window.setFramerateLimit(Setting::FPS);
    _window.setKeyRepeatEnabled(false);

    _layer_focused = NULL;
    _action_id = 0;
  }

  void			clear()
  {
    // Delete each layers
    for (auto layer : _layers)
      delete layer;

    _layers.clear();
    _window.close();
    _map.clearActions();
  }

  void			update()
  {
    int			i;

    _window.clear();

    checkEvent();

    // Start from the end
    for (i = _layers.size() - 1; i >= 0; --i)
    {
      // Check if layer wants to be the last updated
      if (!_layers[i]->update(_window))
	break ;
    }
    // Now we now which one is the main layer - calling the draw on each layer on the top
    for (; i < _layers.size(); ++i)
      _layers[i]->draw(_window);

    _window.display();
  }

  bool			hasLayer()
  {
    return (_layers.size() > 0);
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

  thor::ActionMap<int>				&getMap()
  {
    return (_map);
  }

  thor::ActionMap<int>::CallbackSystem		&getSystem()
  {
    return (_system);
  }

  int						actionId()
  {
    return (_action_id++);
  }

  sf::WindowHandle				getWindowHandle()
  {
    return (_window.getSystemHandle());
  }
}
