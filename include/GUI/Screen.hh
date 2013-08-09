#ifndef SCREEN_HH_
# define SCREEN_HH_

# include <vector>
# include <cstdio>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/System.hpp>
# include "GUI/Layer.hh"
# include "GUI/EventManager.hh"

# include <iostream>

// Screen is the layer manager
// Update them and display them
// Manage mouse depending on the type and location and dispatch it to the appropriate layer
// Keyboard input are managed by callbacks with map & system attributes

// typedef const thor::ActionContext<int> & Context;

enum CursorType { Wait, Text, Normal, Hand };

class Screen
{
  private:
    static sf::RenderWindow	_window;
    static const unsigned	MAX_LAYERS_EXPECTED = 100;

    // Moving - capacity to the user to move the window
    static bool			_moving;
    static sf::Vector2i		_pressed_pos;
    static sf::Vector2i		_old_cursor_pos;
    static void			manageMoving();

    std::vector<Layer *>	_layers;
    Layer			*_layer_focused;
    sf::Clock			_timer;
    EventManager		_event_manager;

    unsigned			getNextId();
    void			checkEvent();
    void			updateFocused();

    // Event catched
    void			pressed(Context context);
    void			released(Context context);
    void			mouseMoved(Context context);
    void			textEntered(Context context);

  public:
    Screen();
    ~Screen();

    static sf::WindowHandle		getHandle();
    static const sf::RenderWindow	&getWindow();
    static void				setMoving(bool moving);
    static sf::Vector2u			getSize();
    static sf::Vector2i			getCursorPosition();
    static bool				isActive();
    static void				restore();
    static void				closeWindow();
    static void				close(Context);
    void				mouseLeft(Context context = sf::Event());

    // Implementation Unix/Windows
    static void				minimize();
    static void				setCursor(CursorType type);

    void				update();
    void				add(Layer *layer);
    void				remove(Layer *layer);
    EventManager			&getEventManager();
};

#endif
