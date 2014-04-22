#ifndef LISTITEM_HH_
# define LISTITEM_HH_

# include "Menu.hh"
# include "Item.hh"
# include "DrawableManager.hh"
# include "Scroller.hh"
# include "EventCallback.hh"

// ListItem : Multiple item scrolling with arrows
// The arrow used the theme of the text : focus if ListItem focus/pressed if arrow focused

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
    ListItem(Item *item, Theme *theme = jag::getTheme("Button"), Alignment align = Left, float scale = 1.0f);
    ~ListItem();

    // ListItem
    void			add(Item *item);
    void			callbackItemChanged(CallbackGui cb);
    Item			*getSelectedItem();
    void			updateRectItem();
    void			setItemTheme(Theme *theme);

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

