#ifndef SERVER_MENU_HH_
# define SERVER_MENU_HH_

# include "GUI/Layer.hh"
# include "GUI/Menu.hh"

class ServerMenu : public Layer
{
  public:
    static const int		WIDTH = 600;
    static const int		HEIGHT = 32;
    static const int		PADDING = 128;
    static const int		MARGIN = 32;

  private:
    Menu			*_menu;

  public:
    ServerMenu(Screen &screen);
    ~ServerMenu();
    void			released(int x, int y);
    void			draw(sf::RenderWindow &window);
    bool			update(sf::RenderWindow &window);
    bool			catchMouse();
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif


