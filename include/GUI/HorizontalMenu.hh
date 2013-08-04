#ifndef HORIZONTAL_MENU_HH_
# define HORIZONTAL_MENU_HH_

# include "GUI/Menu.hh"

# include <iostream>

// Horizontal menu - because the class is not explicit enough

class HorizontalMenu : public Menu
{
  public:
    HorizontalMenu(Rect rec, Theme *theme = jag::getCurrentTheme());
    ~HorizontalMenu();

    const Rect			&getRect() const;
    void			setRect(const Rect &rec);

    void			draw(sf::RenderWindow &win);
    void			update();
};

#endif
