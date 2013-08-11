#ifndef MAIN_MENU_HH_
# define MAIN_MENU_HH_

# include "GUI/Layer.hh"
# include "GUI/Menu.hh"

class MainMenu : public Layer
{
  public:
    static const int		WIDTH = 160;
    static const int		HEIGHT = 200;
    static const int		PADDING = 32;
    static const int		MARGIN = 32;

  private:
    Menu			*_menu;

  public:
    MainMenu();
    ~MainMenu();
    void			released(int x, int y);
    void			draw(sf::RenderWindow &window);
    bool			update(sf::RenderWindow &window);
    bool			catchMouse();
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
