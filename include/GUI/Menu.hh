#ifndef MENU_HH_
# define MENU_HH_

# include <SFML/Graphics.hpp>
# include "Setting.hh"
# include "GUI/Item.hh"
# include "GUI/Action.hh"

// Abstract class for Menu
// Managing all items : input - focus - draw

class Menu : public Action
{
  protected:
    sf::RectangleShape		_border;
    sf::RectangleShape		_box;
    Rect			_rec;
    Theme			*_theme;
    std::vector<Item *>		_items;
    Item			*_item_focused;
    Item			*_item_pressed;

  public:
    Menu(Rect rec, Theme *theme = Setting::getTheme());
    virtual ~Menu();

    const Rect			&getRect() const;
    void			setRect(const Rect &rec);
    void			setTheme(Theme *theme);
    int				getFocused() const;
    int				getPressed() const;
    void			clicked();
    void			add(Item *item);
    void			remove(Item *item);

    virtual void		update() = 0;
    virtual void		draw(sf::RenderWindow &win) = 0;
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual bool		textEntered(const std::string &str);
};

#endif
