#ifndef DRAWABLE_HH_
# define DRAWABLE_HH_

# include "jag.hh"

// Drawable class inherited by all GUI ELement
// Manageable by DrawableManager

class Drawable
{
  protected:
    Rect			_rec;
    Theme			*_theme;
    bool			_focused;

  public:
    virtual ~Drawable() {};

    virtual Rect		getRect() const;
    virtual void		setRect(const Rect &rec);
    virtual void		designChanged() = 0;
    virtual void		setTheme(Theme *_theme);
    virtual void		draw(sf::RenderWindow &win) = 0;
    virtual void		update() = 0;
    Theme			*getTheme();

    // Event
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);
};

#endif
