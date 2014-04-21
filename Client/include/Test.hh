#ifndef TEST_HH_
# define TEST_HH_

# include "Layer.hh"
# include "Menu.hh"
# include "String.hh"
# include "ListBox.hh"
# include "StringArea.hh"
# include "ModalMessageBox.hh"
# include "Table.hh"

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
