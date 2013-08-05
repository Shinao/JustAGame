#ifndef SCREEN_HH_
# define SCREEN_HH_

# include <vector>
# include <cstdio>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/System.hpp>
# include <Thor/Input.hpp>
# include "GUI/Layer.hh"

# include <iostream>

// Screen is the layer manager
// Update them and display them
// Manage mouse depending on the type and location and dispatch it to the appropriate layer
// Keyboard input are managed by callbacks with map & system attributes

// Because fuck static class
// Init at first - clear at the end
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

    // Actions binding
    thor::ActionMap<int>			_map;
    thor::ActionMap<int>::CallbackSystem	_system;
    int						_action_id;

    unsigned			getNextId();
    void			checkEvent();
    void			manageMouse(int x, int y);
    void			manageInput(sf::Event &event);
    void			updateFocused();
  }

  void				init();
  void				clear();
  void				update();
  bool				hasLayer();
  void				add(Layer *layer);
  void				remove(Layer *layer);
  sf::WindowHandle		getWindowHandle();
  const sf::RenderWindow	&getWindow();
  sf::Vector2u			getWindowSize();
  sf::Vector2i			getCursorPosition();

  int						actionId();
  thor::ActionMap<int>				&getMap();
  thor::ActionMap<int>::CallbackSystem		&getSystem();
}

#endif
