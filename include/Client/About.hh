#ifndef ABOUT_HH_
# define ABOUT_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"

class About : public MainMenuItem
{
  public:
    About();
    ~About();

    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif

