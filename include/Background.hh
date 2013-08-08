#ifndef BACKGROUND_HH_
# define BACKGROUND_HH_

#include "GUI/Layer.hh"

class Background : public Layer
{
  private:
    bool			_moving;

  public:
    Background();
    ~Background();
    void			pressed(int x, int y);
    void			released(int x, int y);
    void			minimizeWindow();
    void			restoreWindow();
    void			draw(sf::RenderWindow &window);
    bool			update(sf::RenderWindow &window);
    bool			catchMouse();
    void			mouseLeft();
};

#endif
