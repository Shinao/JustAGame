#ifndef MULTIMEDIA_HH_
# define MULTIMEDIA_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"

class Multimedia : public MainMenuItem
{
  public:
    Multimedia();
    ~Multimedia();
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif


