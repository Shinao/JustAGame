#ifndef TEST_HH_
# define TEST_HH_

# include "GUI/Layer.hh"
# include "GUI/Menu.hh"
# include "GUI/String.hh"
# include "GUI/ListBox.hh"
# include "GUI/StringArea.hh"
# include "GUI/ModalMessageBox.hh"
# include "GUI/Table.hh"

class Test : public Layer
{
  public:
    static const int		HEIGHT = 64;

  private:

  public:
    Test();
    ~Test();
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
