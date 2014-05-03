#ifndef INPUT_LAYER_HH_
# define INPUT_LAYER_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"

class InputLayer : public MainMenuItem
{
  public:
    InputLayer();
    ~InputLayer();

    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
