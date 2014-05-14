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
    typedef std::function<void ()> CallbackGui;

    enum State
    {
      DoubleClicked,
      Pressed,
      Released,
      Focused,
      Unfocused
    };

  protected:
    static const int		DelayTooltip = 750;
    static const int		DelayDoubleClick = 300;

    Rect			_rec;
    Theme			*_theme;

    sf::Clock			_timer_double_click;

    // Event
    bool			_enabled;
    bool			_focused;
    bool			_pressed;
    bool			_release;
    CallbackGui			_callback_pressed;
    CallbackGui			_callback_double_click;
    CallbackGui			_callback_released;
    CallbackGui			_callback_focused;
    CallbackGui			_callback_unfocused;

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
    void			setState(State state);
    void			addCallback(CallbackGui callback, State state = Pressed);
    bool			isFocused() const;
    bool			isEnabled() const;
    void			enable(bool enable);
    bool			isPressed() const;
    void			autoRelease(bool unpress);
    void			released();
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);
};

#endif
