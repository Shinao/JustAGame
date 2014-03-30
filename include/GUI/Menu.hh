#ifndef MENU_HH_
# define MENU_HH_

# include "jag.hh"
# include "GUI/Item.hh"
# include "GUI/Drawable.hh"

// Abstract class for Menu
// Managing all items : input - focus - draw
// Menu must be updated when a change occur to avoid unnecesary proccess
// When it gets a new Item, it will manage it

class Menu : public Drawable
{
  public:
    enum Type
    {
      Horizontal,
      Vertical
    };

  protected:
    Type			_type;
    sf::RectangleShape		_box;
    sf::RectangleShape		_border;
    Border::Type		_border_type;
    std::vector<Item *>		_items;
    Item			*_item_focused;
    Item			*_item_pressed;
    sf::Vector2i		_margin;
    bool			_shrink;

  public:
    Menu(Type type, Rect rec, Theme *theme = jag::getCurrentTheme());
    virtual ~Menu();

    void			setTheme(Theme *theme);
    void			setPressed(Item *item);
    void			mouseReleased(int x, int y);
    void			add(Item *item);
    void			remove(Item *item);
    void			setMargin(const sf::Vector2i &margin);
    void			setBorder(Border::Type border);
    void			shrinkToFit(bool shrink);

    void			update();
    void			draw(sf::RenderWindow &win);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
    void			designChanged();
};

#endif
