#ifndef TEST_HH_
# define TEST_HH_

# include "GUI/Layer.hh"
# include "GUI/Menu.hh"
# include "GUI/String.hh"
# include "GUI/ListBox.hh"

class Test : public Layer
{
  public:
    static const int		HEIGHT = 64;

  private:
    Menu			*_menu;

  public:
    Test();
    ~Test();
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif

