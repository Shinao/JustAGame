#ifndef HORIZONTAL_MENU_HH_
# define HORIZONTAL_MENU_HH_

# include "Screen/Menu.hh"

// Horizontal menu - because the class is not explicit enough

class HorizontalMenu : public Menu
{
  private:
    HorizontalMenu();

  public:
    ~HorizontalMenu();

    const Rect			&getRect() const;
    void			setRect(const Rect &rec);

    void			draw();
    void			update();
};

#endif
