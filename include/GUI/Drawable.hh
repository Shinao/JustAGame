#ifndef DRAWABLE_HH_
# define DRAWABLE_HH_

# include "jag.hh"

// Fucking include
class Tooltip;

// Drawable class inherited by all GUI ELement
// Manageable by DrawableManager

class Drawable
{
  protected:
    static const int		DelayTooltip = 1000;

    Rect			_rec;
    Theme			*_theme;
    bool			_focused;

    // Tooltip
    Tooltip			*_tooltip;
    sf::Clock			_timer_tooltip;
    sf::String			_text_tooltip;

  public:
    Drawable(Theme *theme = jag::getCurrentTheme());
    virtual ~Drawable() {};

    virtual Rect		getRect() const;
    virtual void		setRect(const Rect &rec);
    virtual void		designChanged() = 0;
    virtual void		setTheme(Theme *_theme);
    virtual void		draw(sf::RenderWindow &win);
    virtual void		update() = 0;
    Theme			*getTheme();

    // Tooltip
    void			removeTooltip();
    void			setTooltip(const sf::String &text);

    // Event
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);
};

#endif
