#ifndef VERTICAL_MENU_HH_
# define VERTICAL_MENU_HH_

# include "GUI/Menu.hh"

// Vertical menu - because the class is not explicit enough

class VerticalMenu : public Menu
{
  private:
    int				_filled_height;

  public:
    VerticalMenu(Rect rec, Theme *theme = jag::getCurrentTheme());
    ~VerticalMenu();

    void			update();
    Rect			getFilledRect() const;
    void			initBorders();
};

#endif

