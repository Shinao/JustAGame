#ifndef MULTIMEDIA_HH_
# define MULTIMEDIA_HH_

# include "Layer.hh"
# include "Menu.hh"

class Multimedia : public Layer
{
  public:
    static const int		WIDTH = 600;
    static const int		HEIGHT = 32;
    static const int		PADDING = 128;
    static const int		MARGIN = 32;

  private:
    Menu			*_menu;

  public:
    Multimedia();
    ~Multimedia();
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif


