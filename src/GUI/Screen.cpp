#include <SFML/System.hpp>
#include <sstream>
#include "Screen.hh"
#include "jag.hh"
#include "OSSpecific.hh"
#include "Ressource.hh"


namespace Screen
{
  //
  // Private properties
  //

  namespace
  {
    // Using a pointer since we can't do global variable Window with Shared Library
    sf::RenderWindow	*_window = NULL;

    const unsigned	MAX_LAYERS_EXPECTED = 100;

    // Moving - capacity to the user to move the window
    bool			_moving;
    sf::Vector2i		_pressed_pos;
    sf::Vector2i		_old_cursor_pos;
    void			manageMoving();
    Mode			_mode;
    bool			_display_ig_setting;

    std::vector<Layer *>	_layers_to_remove;
    std::vector<Layer *>	_layers;
    std::vector<Layer *>	_layers_setting;
    Layer			*_layer_focused;
    Layer			*_current_layer;
    sf::Clock			_timer_wait;
    EventManager		*_event_manager;

    void			catchLayersEvents();
    unsigned			getNextId();
    void			checkEvent();
    void			updateFocused();
    void			manageLayers();
    void			resetIDs();

    // Event catched
    void			mousePressed(Context context);
    void			mouseReleased(Context context);
    void			mouseMoved(Context context);
  }




  // 
  // Private 
  // 

  namespace
  {
    void			catchLayersEvents()
    {
      // Add special event callback
      using namespace std::placeholders;
      _event_manager->add(Action(sf::Event::Closed), std::bind(&Screen::close, _1));
      _event_manager->add(Action(sf::Event::MouseButtonPressed, sf::Mouse::Left),
	  std::bind(&Screen::mousePressed, _1));
      _event_manager->add(Action(sf::Event::MouseButtonReleased, sf::Mouse::Left),
	  std::bind(&Screen::mouseReleased, _1));
      _event_manager->add(Action(sf::Event::MouseMoved), std::bind(&Screen::mouseMoved, _1));
      _event_manager->add(Action(sf::Event::MouseLeft), std::bind(&Screen::mouseLeft, _1));
      _event_manager->add(Action(sf::Event::LostFocus), std::bind(&Screen::mouseLeft, _1));
    }

    unsigned			getNextId()
    {
      // Check not enough space : double capacity
      if (_layers.size() >= _layers.capacity())
	_layers.reserve(_layers.capacity() + MAX_LAYERS_EXPECTED);

      return (_layers.size());
    }

    void				checkEvent()
    {
      sf::Event			event;

      // Check if user wants to move the window
      manageMoving();

      // Everything is done by callbacks - thanks C++11
      while (_window->pollEvent(event))
	_event_manager->push(event);

      // All event pushed - time to callback
      _event_manager->invokeCallbacks();
    }

    void				mousePressed(Context context)
    {
      int	x = context.mouseButton.x, y = context.mouseButton.y;

      if (_layer_focused != NULL)
	_layer_focused->mousePressed(x, y);
    }

    void				mouseReleased(Context context)
    {
      int	x = context.mouseButton.x, y = context.mouseButton.y;

      if (_layer_focused != NULL)
	_layer_focused->mouseReleased(x, y);
    }

    void				manageMoving()
    {
      if (_moving)
      {
	// Get the new position of the cursor
	sf::Vector2i cursor_pos = sf::Mouse::getPosition();

	// Move the window depending on where we were when pressed
	// Only if the position of the cursor has changed
	if (cursor_pos != _old_cursor_pos)
	{
	  _window->setPosition(cursor_pos - _pressed_pos);
	  _old_cursor_pos = cursor_pos;
	}
      }
    }

    void				mouseMoved(Context)
    {
      // Get the new focus
      updateFocused();
    }

    void				updateFocused()
    {
      sf::Vector2i	cur = sf::Mouse::getPosition(*_window);
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
	  _layer_focused->mouseCaught(cur.x, cur.y);
	  return ;
	}
      }

      _layer_focused = NULL;
    }

    void				manageLayers()
    {
      if (_layers_to_remove.size() == 0)
	return ;

      for (auto layer : _layers_to_remove)
      {
	if (layer == _layer_focused)
	  _layer_focused = NULL;

	// Moving all the layer from one index down
	for (unsigned i = layer->getId(); i + 1 < _layers.size(); ++i)
	{
	  _layers[i] = _layers[i + 1];
	  _layers[i]->setId(_layers[i]->getId() - 1);
	}

	_layers.pop_back();
	delete layer;
      }

      _layers_to_remove.clear();

      // Update focused in case we deleted it
      updateFocused();
    }

    void				resetIDs()
    {
      for (unsigned i = 0; i < _layers.size(); ++i)
	_layers[i]->setId(i);
    }
  }





  // 
  // Public 
  // Implementation methods
  //

  void			init()
  {
    _event_manager = new EventManager();
    _moving = false;
    _layer_focused = NULL;

    // Get enough space
    _layers.reserve(MAX_LAYERS_EXPECTED);

    // Setting mode
    setMode(Setting);

    // Icon
    _window->setIcon(jag_icon.width,  jag_icon.height,  jag_icon.pixel_data);

    catchLayersEvents();
  }

  void			setMode(Mode mode)
  {
    sf::VideoMode	video_mode;
    sf::Uint32		style = sf::Style::None;
    bool		first_init = true;

    _mode = mode;

    if (_window != NULL)
    {
      delete _window;
      first_init = false;
    }

    // Swap from game layers to setting layer and vice versa
    _layers.swap(_layers_setting);

    // Create the window depending on the mode
    if (mode == Setting)
    {
      // Empty our previous game
      _layers_setting.clear();
      _display_ig_setting = false;

      video_mode.width = jag::ClientWidth;
      video_mode.height = jag::ClientHeight;
    }
    else
    {
      CSimpleIniA	&ini = jag::getSettings();

      if (ini.GetBoolValue(INI_GROUP, "video_fullscreen", true) == true)
	style |= sf::Style::Fullscreen;

      std::string	resolution = ini.GetValue(INI_GROUP, "video_resolution", "");
      std::stringstream	ss;
      char		c;
      ss << resolution;
      ss >> video_mode.width >> c >> video_mode.height;

      if (!video_mode.isValid())
	video_mode = sf::VideoMode::getFullscreenModes()[0];
    }

    resetIDs();

    _window = new sf::RenderWindow(video_mode, jag::WindowName, sf::Style::None);

    if (mode == Setting)
      restore();

    // Setting changed - update layers
    if (!first_init)
    {
      for (auto layer : _layers)
	layer->settingChanged();
      for (auto layer : _layers_setting)
	layer->settingChanged();
    }

    // TODO - Wait until finished if needed to remove it
    // _window->setKeyRepeatEnabled(false);
  }

  void			clear()
  {
    delete _window;

    for (auto layer : _layers)
      delete layer;
  }

  void				update()
  {
    int			i;

    checkEvent();

    // Start from the end
    for (i = _layers.size() - 1; i >= 0; --i)
    {
      _current_layer = _layers[i];
      // Check if layer wants to be the last updated
      // TODO Remove useless feature non-update ?
      if (!_current_layer->update(*_window))
      {
	--i;
	break ;
      }
    }

    // Safety first - put your seat belt on please
    ++i;

    _window->clear(sf::Color::Blue);

    // Now we know which one is the main layer - calling the draw on each layer on the top
    for (unsigned i = 0; (unsigned) i < _layers.size(); ++i)
    {
      _current_layer = _layers[i];
      _current_layer->draw(*_window);
    }

    // Waiting FPS frames
    while (_timer_wait.getElapsedTime().asMilliseconds() < jag::FPSTime);
    _timer_wait.restart();

    _window->display();

    // Safely remove layers if asked and things
    manageLayers();
  }

  void				add(Layer *layer)
  {
    unsigned		id = getNextId();

    _layers.push_back(layer);
    layer->setId(id);
    updateFocused();

    // If IG Setting enabled : add it to our setting layers if current layer is setting
    if (_display_ig_setting && layer->getType() == Layer::Setting)
      _layers_setting.push_back(layer);
  }

  void				remove(Layer *layer)
  {
    _layers_to_remove.push_back(layer);

    // If IG Setting enabled : remove it to our setting layers if layer is setting
    if (_display_ig_setting && layer->getType() == Layer::Setting)
      removeFromSetting(layer);
  }

  void				removeFromSetting(Layer *layer)
  {
    for (auto it = _layers_setting.begin(); it != _layers_setting.end(); ++it)
      if (*it == layer)
      {
	_layers_setting.erase(it);
	  return ;
      }
  }

  sf::WindowHandle			getHandle()
  {
    return (_window->getSystemHandle());
  }

  const sf::RenderWindow		&getWindow()
  {
    return (*_window);
  }

  sf::Vector2u				getSize()
  {
    return (_window->getSize());
  }

  sf::Vector2i				getCursorPosition()
  {
    return (sf::Mouse::getPosition(*_window));
  }

  void					close(Context)
  {
    closeWindow();
  }

  void					closeWindow()
  {
    _window->close();
  }

  bool					isActive()
  {
    return (_window->isOpen());
  }

  EventManager				&getEventManager()
  {
    return (*_event_manager);
  }

  void					minimize()
  {
    minimizeImpl(_window->getSystemHandle());
  }

  void					setCursor(CursorType type)
  {
    setCursorImpl(_window->getSystemHandle(), type);
  }

  void					openUrl(const std::string &url)
  {
    openUrlImpl(url);
  }

  void						restore()
  {
    sf::VideoMode	screen = sf::VideoMode::getDesktopMode();

    _window->setPosition(sf::Vector2i(screen.width / 2 - getSize().x / 2,
	  screen.height / 2 - getSize().y / 2));
  }

  void					setMoving(bool moving)
  {
    _moving = moving;

    if (_moving)
      _pressed_pos = sf::Mouse::getPosition() - _window->getPosition();
  }

  void					mouseLeft(Context)
  {
    if (_moving)
      manageMoving();
    else
    {
      if (_layer_focused != NULL)
	_layer_focused->mouseLeft();
    }
  }

  void					scissor(Rect rec)
  {
    // Draw only in our area with View
    sf::View view(sf::FloatRect(rec.left, rec.top, rec.width, rec.height));

    view.setViewport(sf::FloatRect((float) rec.left / _window->getSize().x,
	  (float) rec.top / _window->getSize().y, (float) rec.width / _window->getSize().x,
	  (float) rec.height / _window->getSize().y));

    _window->setView(view);
  }

  void					undoScissor()
  {
    _window->setView(_window->getDefaultView());
  }

  void					toggleIGSetting()
  {
    _display_ig_setting = !_display_ig_setting;

    if (_display_ig_setting)
    {
      _layers.insert(_layers.end(), _layers_setting.begin(), _layers_setting.end());
      _layer_focused = NULL;
      updateFocused();
      return ;
    }

    // Remove all layers contained in setting layers
    for (auto setting : _layers_setting)
      for (auto it = _layers.begin(); it != _layers.end(); ++it)
	if (*it == setting)
	{
	  _layers.erase(it);
	  break ;
	}

    resetIDs();

    // Update our focused in case our setting layers had the focus
    if (_layer_focused != NULL)
      _layer_focused->mouseLeft();
    _layer_focused = NULL;
    updateFocused();
  }

  Mode					getMode()
  {
    return (_mode);
  }
}
