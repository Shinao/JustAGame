#ifndef MENU_HH_
# define MENU_HH_

# include <SFML/Graphics.hpp>
# include "jag.hh"
# include "GUI/Item.hh"

// Abstract class for Menu
// Managing all items : input - focus - draw
// Menu must be updated when a change occur to avoid unnecesary proccess
// When it gets a new Item, it will manage it

class Menu
{
  protected:
    sf::RectangleShape		_box;
    sf::RectangleShape		_border;
    Border::Type		_border_type;
    Rect			_rec;
    Theme			*_theme;
    std::vector<Item *>		_items;
    Item			*_item_focused;
    Item			*_item_pressed;
    int				_margin;

  public:
    Menu(Rect rec, Theme *theme = jag::getCurrentTheme());
    virtual ~Menu();

    const Rect			&getRect() const;
    void			setRect(const Rect &rec);
    void			setTheme(Theme *theme);
    void			setPressed(Item *item);
    void			clicked();
    void			add(Item *item);
    void			remove(Item *item);
    void			setMargin(int margin);
    void			setBorder(Border::Type border);

    virtual void		update() = 0;
    virtual void		draw(sf::RenderWindow &win);
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual bool		textEntered(const std::string &str);
    virtual Rect		getFilledRect() const = 0;
    virtual void		themeChanged();
};

#endif
