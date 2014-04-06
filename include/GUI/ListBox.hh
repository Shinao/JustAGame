#ifndef LISTBOX_HH_
# define LISTBOX_HH_

# include "GUI/Menu.hh"
# include "GUI/String.hh"
# include "GUI/DrawableManager.hh"
# include "GUI/Scroller.hh"
# include "EventCallback.hh"

// ListBox : hide/show a menu
// Use a Scroller if too big

class ListBox : public Item, public DrawableManager, public EventCallback
{
  private:
    Scroller			*_scroller;
    Menu			*_menu;
    String			*_button;
    bool			_is_open;
    Item			*_selected_item;
    bool			_patch_has_moved;
    CallbackGui			_callback_item_changed;

  public:
    ListBox(String *item, Theme *theme = jag::getTheme("Button"), Alignment align = Left, float scale = 1.0f);
    ~ListBox();

    // ListBox
    bool			isOpen();
    void			toggle();
    void			add(String *item);
    void			callbackItemChanged(CallbackGui cb);
    Item			*getSelectedItem();
    void			released();

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
