#ifndef MAIN_MENU_HH_
# define MAIN_MENU_HH_

# include "Layer.hh"
# include "Menu.hh"

#include <iostream>

class MainMenu : public Layer
{
  public:
    static const int		WIDTH = 160;
    static const int		HEIGHT = 400;
    static const int		PADDING = 32;
    static const int		MARGIN = 32;

  private:
    Menu			*_menu;
    Layer			*_layer_menu;
    void			cbServer();
    void			cbPlayer();
    void			cbKeyBindings();
    void			cbAudio();
    void			cbVideo();
    void			cbReleased();

  public:
    MainMenu();
    ~MainMenu();
    void			mousePressed(int x, int y);
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
