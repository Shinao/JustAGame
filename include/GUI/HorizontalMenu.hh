#ifndef HORIZONTAL_MENU_HH_
# define HORIZONTAL_MENU_HH_

# include "GUI/Menu.hh"

# include <iostream>

// Horizontal menu - because the class is not explicit enough

class HorizontalMenu : public Menu
{
  private:
    int				_filled_width;

  public:
    HorizontalMenu(Rect rec, Theme *theme = jag::getCurrentTheme());
    ~HorizontalMenu();

    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getFilledRect() const;
    void			themeChanged();
};

#endif
