#ifndef GAMELAYER_HH_
# define GAMELAYER_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"

class GameLayer : public MainMenuItem
{
  public:
    GameLayer();
    ~GameLayer();

    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif

