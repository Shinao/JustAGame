#ifndef SCREEN_HH_
# define SCREEN_HH_

# include "Layer.hh"
# include "EventManager.hh"

#include <iostream>

// Screen is the layer manager
// Update them and display them
// Manage mouse depending on the type and location and dispatch it to the appropriate layer
// Keyboard input are managed by callbacks with map & system attributes
// Can use scissor do draw only in specified location

namespace Screen
{
  //
  // Public propeties
  //

  enum	Mode
  {
    Game,
    Setting
  };

  void				init();
  void				clear();
  void				toggleMode();
  Mode				getMode();

  sf::WindowHandle		getHandle();
  const sf::RenderWindow	&getWindow();
  void				setMoving(bool moving);
  sf::Vector2u			getSize();
  sf::Vector2i			getCursorPosition();
  bool				isActive();
  void				restore();
  void				closeWindow();
  void				close(Context);
  void				mouseLeft(Context context = sf::Event());
  void				scissor(Rect rec);
  void				undoScissor();
  void				toggleIGSetting();

  void				update();
  void				add(Layer *layer);
  void				remove(Layer *layer);
  void				removeFromSetting(Layer *layer);
  EventManager			&getEventManager();

  // Implementation Unix/Windows
  void				minimize();
  void				setCursor(CursorType type);
  void				openUrl(const std::string &url);

  // TODO - Remove debug
  void	debug(int debug);
}

#endif
