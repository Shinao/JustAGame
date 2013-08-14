#ifndef BACKGROUND_HH_
# define BACKGROUND_HH_

# include "GUI/Layer.hh"

class Background : public Layer
{
  private:
    bool			_moving;
    sf::RectangleShape		_bg;

  public:
    Background(Screen &screen);
    ~Background();
    void			pressed(int x, int y);
    void			released(int x, int y);
    void			draw(sf::RenderWindow &window);
    bool			update(sf::RenderWindow &window);
    bool			catchMouse();
};

#endif
