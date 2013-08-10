#ifndef MAIN_MENU_HH_
# define MAIN_MENU_HH_

# include "GUI/Layer.hh"
# include "GUI/VerticalMenu.hh"

class MainMenu : public Layer
{
  private:
    VerticalMenu		*_menu;

  public:
    MainMenu();
    ~MainMenu();
    void			released(int x, int y);
    void			draw(sf::RenderWindow &window);
    bool			update(sf::RenderWindow &window);
    bool			catchMouse();
};

#endif
