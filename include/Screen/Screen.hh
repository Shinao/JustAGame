#ifndef SCREEN_HH_
# define SCREEN_HH_

# include <vector>
# include <cstdio>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/System.hpp>
# include "Screen/Layer.hh"
# include "Utility/Physic.hh"
# include "Setting.hh"

# include <iostream>

// Screen is the layer manager
// Update them and display them
// Manage input depending on the type and location
// and dispatch them to the appropriate layer

// Because fuck static class
// Init at first - clear at the end
namespace Screen
{
  // Private attributes - methods
  namespace
  {
    const unsigned		MAX_LAYERS_EXPECTED = 100;
    const unsigned		WINDOW_WIDTH = 800;
    const unsigned		WINDOW_HEIGHT = 500;
    std::vector<Layer *>	_layers;
    sf::RenderWindow		_window;
    Layer			*_layer_focused;

    unsigned			getNextId();
    void			checkEvent();
    void			manageKeyboard(sf::Event &event);
    void			manageMouse(int x, int y);
    void			updateFocused();
  }

  void				init();
  void				clear();
  void				update();
  bool				hasLayer();
  void				add(Layer *layer);
  void				remove(Layer *layer);
}

#endif
