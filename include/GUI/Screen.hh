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
  void				init();
  void				clear();
  void				update();
  void				add(Layer *layer);
  void				remove(Layer *layer);
  void				close(Context);
  void				closeWindow();
  bool				isActive();
  void				restore();
  void				minimize();
  sf::WindowHandle		getHandle();
  const sf::RenderWindow	&getWindow();
  sf::Vector2u			getSize();
  sf::Vector2i			getCursorPosition();
  EventManager			&getEventManager();
}

#endif
