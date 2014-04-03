#ifndef DRAWABLE_HH_
# define DRAWABLE_HH_

# include "jag.hh"

// Fucking include
class Tooltip;

// Drawable class inherited by all GUI ELement
// Manageable by DrawableManager

class Drawable
{
  public:
    typedef std::function<void ()> Callback;

    enum State
    {
      Pressed,
      Released,
      Focused,
      Unfocused
    };

  protected:
    static const int		DelayTooltip = 1000;

    Rect			_rec;
    Theme			*_theme;

    // Event
    bool			_focused;
    bool			_pressed;
    bool			_release;
    Callback			_callback_pressed;
    Callback			_callback_released;
    Callback			_callback_focused;
    Callback			_callback_unfocused;

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
    void			addCallback(Callback callback, State state = Pressed);
    bool			isFocused() const;
    bool			isPressed() const;
    void			autoRelease(bool unpress);
    void			released();
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);
};

#endif
