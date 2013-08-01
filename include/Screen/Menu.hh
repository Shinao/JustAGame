#ifndef MENU_HH_
# define MENU_HH_

# include <SFML/Graphics.hpp>
# include "Setting.hh"
# include "Screen/Item.hh"

// Abstract class for Menu
// Managing all items : input - focus - draw

class Menu
{
  protected:
    Rect			_rec;
    Theme			*_theme;
    std::vector<Item *>		_items;

  public:
    Menu(Rect rec, Theme *theme = Setting::getTheme());
    virtual ~Menu();

    const Rect			&getRect() const;
    void			setRect(const Rect &rec);
    void			setTheme(Theme *theme);

    virtual void		add(Item *item);
    virtual void		remove(Item *item);
    virtual void		update() = 0;
    virtual void		draw() = 0;
};

#endif
