#ifndef SCREEN_HH_
# define SCREEN_HH_

# include <vector>
# include <cstdio>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/System.hpp>
# include <Thor/Input.hpp>
# include "GUI/Layer.hh"
# include "GUI/EventManager.hh"

# include <iostream>

// Screen is the layer manager
// Update them and display them
// Manage mouse depending on the type and location and dispatch it to the appropriate layer
// Keyboard input are managed by callbacks with map & system attributes

// Because fuck static class
// Init at first - clear at the end

// typedef const thor::ActionContext<int> & Context;

namespace Screen
{
  // Private attributes - methods
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
    void			manageMouse(Context context);
    void			manageInput(Context context);
    void			updateFocused();
    void			manageClick(Context context);
  }

  void				init();
  void				clear();
  void				update();
  void				add(Layer *layer);
  void				remove(Layer *layer);
  void				close(Context);
  bool				isActive();
  sf::WindowHandle		getWindowHandle();
  const sf::RenderWindow	&getWindow();
  sf::Vector2u			getWindowSize();
  sf::Vector2i			getCursorPosition();
}

#endif
