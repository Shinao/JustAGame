#ifndef TITLEBAR_HH_
# define TITLEBAR_HH_

# include "GUI/Layer.hh"
# include "GUI/HorizontalMenu.hh"

class Titlebar : public Layer
{
  private:
    const int			TITLEBAR_HEIGHT = 36;
    HorizontalMenu		*_menu;

  public:
    Titlebar();
    ~Titlebar();
    void			clicked();
    void			draw(sf::RenderWindow &window);
    bool			update(sf::RenderWindow &window);
    bool			catchMouse();
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
