#ifndef ITEM_HH_
# define ITEM_HH_

# include "jag.hh"

// Abstract class item for text & sprite
// Object depending on a menu
// Item should always have a theme
// Item has an ID useful for the getPressed and Focused function of the menu

class Item
{
  public:
    typedef std::function<void ()> Callback;

    enum Alignment
    {
      Left,
      Right,
      Center
    };

    enum State
    {
      Pressed,
      Released
    };

  protected:
    bool			_focused;
    bool			_pressed;
    bool			_release;
    Theme			*_theme;
    Rect			_rec;
    Alignment			_align;
    float			_scale;
    sf::Vector2i		_margin;
    sf::RectangleShape		_box;
    Callback			_callback_pressed;
    Callback			_callback_released;
    sf::RectangleShape		_border;
    Border::Type		_border_type;

  public:
    Item(Theme *theme = jag::getCurrentTheme(), Alignment align = Left, float scale = 1.0f);
    virtual ~Item();

    const sf::Vector2i		&getMargin() const;
    void			setMargin(const sf::Vector2i &margin);
    void			setTheme(Theme *theme);
    Theme			*getTheme();
    Rect			getRect() const;
    virtual void		setRect(const Rect &rec);
    void			setAlignment(Alignment align);
    Alignment			getAlignment();
    sf::Vector2i		getRessourcePosition();
    void			addCallback(Callback callback, State state = Pressed);
    bool			isFocused() const;
    bool			isPressed() const;
    void			autoRelease(bool unpress);
    void			setBorder(Border::Type border);

    virtual Rect		getRectRessource() const = 0;
    virtual void		draw(sf::RenderWindow &win);
    virtual void		update() = 0;
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		pressed();
    virtual void		released();
    virtual void		designChanged();
};

#endif
