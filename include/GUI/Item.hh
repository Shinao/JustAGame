#ifndef ITEM_HH_
# define ITEM_HH_

# include "jag.hh"

// Abstract class item for text & sprite
// Object depending on a menu
// Item should always have a theme
// Item has an ID usefull for the getPressed and Focused function of the menu

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

  protected:
    bool			_focused;
    bool			_pressed;
    bool			_release;
    Theme			*_theme;
    Rect			_rec;
    Alignment			_align;
    float			_scale;
    int				_margin;
    sf::RectangleShape		_box;
    sf::RectangleShape		_border;
    std::function<void ()>	_callback;

  public:
    Item(Theme *theme = jag::getCurrentTheme(), Alignment align = Left, float scale = 1.0f);
    virtual ~Item();

    int				getMargin() const;
    void			setMargin(int margin);
    void			setTheme(Theme *theme);
    Theme			*getTheme();
    Rect			getRect() const;
    virtual void		setRect(const Rect &rec);
    void			setAlignment(Alignment align);
    Alignment			getAlignment();
    sf::Vector2i		getRessourcePosition();
    void			addCallback(Callback callback);
    void			removeCallback();
    bool			isFocused() const;
    bool			isPressed() const;
    void			autoRelease(bool unpress);

    virtual Rect		getRectRessource() const = 0;
    virtual bool		textEntered(const std::string &str);
    virtual void		draw(sf::RenderWindow &win);
    virtual void		update() = 0;
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		pressed();
    virtual void		released();
    virtual void		designChanged();
};

#endif
