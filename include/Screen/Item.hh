#ifndef ITEM_HH_
# define ITEM_HH_

# include "Setting.hh"
# include "Screen/Theme.hh"

// Abstract class item for text & sprite

class Item
{
  private:
    Theme			*_theme;
    Rect			_rec;

  public:
    Item(Theme *theme = NULL);
    virtual ~Item();

    void			setTheme(Theme *theme);
    const Rect			&getRect() const;
    void			setRect(const Rect &rec);
};

#endif
