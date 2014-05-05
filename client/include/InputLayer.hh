#ifndef INPUT_LAYER_HH_
# define INPUT_LAYER_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"

class InputLayer : public MainMenuItem
{
  private:
    static const int		NB_INPUT = 5;

    static struct Keys
    {
      std::string		ini_name;
      std::string		label;
      sf::Keyboard::Key		sf_key;
    }				_keys[NB_INPUT];

    void			applyChanges();

  public:
    InputLayer();
    ~InputLayer();

    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
