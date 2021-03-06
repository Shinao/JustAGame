#ifndef LISTITEM_HH_
# define LISTITEM_HH_

# include "GUI/Menu.hh"
# include "GUI/Item.hh"
# include "GUI/DrawableManager.hh"
# include "GUI/Scroller.hh"
# include "GUI/EventCallback.hh"

// ListItem : Multiple item scrolling with arrows
// The arrow used the theme of the border : arrow focus -> border pressed else border focused
// Add at least one element before drawing a ListItem : It shouldn't be empty

class ListItem : public Item
{
  private:
    std::vector<Item *>		_items;
    int				_selected_item;
    CallbackGui			_callback_item_changed;
    sf::ConvexShape		_arrow_left;
    sf::ConvexShape		_arrow_right;
    bool			_arrow_left_focused;
    bool			_arrow_right_focused;
    Rect			_max_rec;
    Theme			*_item_theme;

    static const int		ARROW_SIZE = 12;
    static const int		ARROW_THICKNESS = 2;
    static const int		ARROW_PADDING = 4;

  public:
    ListItem(Theme *theme = jag::getTheme("Button"), float scale = 1.0f);
    ~ListItem();

    // ListItem
    void			add(Item *item);
    void			callbackItemChanged(CallbackGui cb);
    Item			*getSelectedItem();
    void			updateRectItem();
    void			setItemTheme(Theme *theme);
    void			setSelectedItem(Item *item);
    void			setSelectedIndex(int index);

    void			setRect(const Rect &rec);
    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getRectRessource() const;
    void			designChanged();

    // Event
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);
};

#endif

