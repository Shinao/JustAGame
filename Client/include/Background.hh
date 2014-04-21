#ifndef BACKGROUND_HH_
# define BACKGROUND_HH_

# include "Layer.hh"

class Background : public Layer
{
  private:
    bool			_moving;
    sf::RectangleShape		_bg;

  public:
    Background();
    ~Background();
    void			mousePressed(int x, int y);
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
};

#endif
