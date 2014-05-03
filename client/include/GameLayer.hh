#ifndef GAMELAYER_HH_
# define GAMELAYER_HH_

# include "Layer.hh"
# include "Menu.hh"

class GameLayer : public Layer
{
  public:
    static const int		WIDTH = 600;
    static const int		HEIGHT = 32;
    static const int		PADDING = 128;
    static const int		MARGIN = 32;

  private:
    Menu			*_menu;

  public:
    GameLayer();
    ~GameLayer();
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif

