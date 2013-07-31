#include "Screen/Screen.hh"

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

	// Manage keyboard and mouse
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased || 
	    event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
	  manageKeyboard(event);
	else if (event.type == sf::Event::MouseMoved)
	  manageMouse(event.mouseMove.x, event.mouseMove.y);
      }
    }

    void			manageKeyboard(sf::Event &event)
    {
      // Start from the end and go down until a layer catch it
      for (int i = _layers.size() - 1; i >= 0; --i)
	if (_layers[i]->catchEvent(event))
	  return ;
    }

    void			manageMouse(int x, int y)
    {
      // If we have a layer focused
      if (_layer_focused != NULL)
      {
	// Check if still on the same layer to avoid unnecessary check
	if (Physic::isPointIn(x, y, _layer_focused->getX(), _layer_focused->getY(), _layer_focused->getWidth(), _layer_focused->getHeight()))
	{
	  _layer_focused->mouseMoved(x, y);
	  return ;
	}

	// No ? Tell it lost focus
	_layer_focused->mouseLeft();
      }

      // Get the new focus and call it
      updateFocused();
      if (_layer_focused != NULL)
	_layer_focused->mouseMoved(x, y);
    }

    void			updateFocused()
    {
      sf::Vector2i		cur = sf::Mouse::getPosition(_window);
      Layer			*ly;

      for (int i = _layers.size() - 1; i >= 0; --i)
      {
	ly = _layers[i];
	if (Physic::isPointIn(cur.x, cur.y, ly->getX(), ly->getY(), ly->getWidth(), ly->getHeight()))
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
    for (unsigned i = 0; i < _layers.capacity(); ++i)
      _layers[i] = NULL;

    // Recreate the window
    _window.create(sf::VideoMode(Setting::windowWidth, Setting::windowHeight), "JustAGame");

    _layer_focused = NULL;
  }

  void			clear()
  {
    // Delete each layers
    for (unsigned i = 0; i < _layers.size(); ++i)
      delete _layers[i];

    _layers.clear();
    _window.close();
  }

  void			update()
  {
    _window.clear();

    checkEvent();

    // Start from the end
    for (int i = _layers.size() - 1; i >= 0; --i)
    {
      // Check if layer wants to be the last updated
      if (!_layers[i]->update(_window))
	break ;
    }

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
}
