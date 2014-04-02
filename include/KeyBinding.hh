#ifndef KEY_BINDING_HH_
# define KEY_BINDING_HH_

# include "GUI/Layer.hh"

class KeyBinding : public Layer
{
  public:
    static const int		WIDTH = 600;
    static const int		HEIGHT = 32;
    static const int		PADDING = 128;
    static const int		MARGIN = 32;

  private:

  public:
    KeyBinding();
    ~KeyBinding();
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
