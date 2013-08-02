#ifndef ITEM_HH_
# define ITEM_HH_

# include "Setting.hh"

// Abstract class item for text & sprite
// Object depending on a menu
// Item should always have a theme
// Item has an ID usefull for the getPressed and Focused function of the menu

class Item
{
  public:
    enum Alignment
    {
      Left,
      Right,
      Center
    };

  protected:
    int				_margin;
    float			_scale;
    Theme			*_theme;
    Rect			_rec;
    Alignment			_align;
    sf::RectangleShape		_box;
    int				_id;

  public:
    Item(int id, Theme *theme = NULL, Alignment align = Left, float scale = 1.0f);
    virtual ~Item();

    int				getMargin();
    void			setMargin(int margin);
    void			setTheme(Theme *theme);
    Theme			*getTheme();
    Rect			getRect() const;
    const Rect			&getRectRessource() const;
    virtual void		setRect(const Rect &rec);
    void			setAlignment(Alignment align);
    Alignment			getAlignment();
    void			setId(int id);
    int				getId() const;

    virtual bool		textEntered(const std::string &str);
    virtual void		draw(sf::RenderWindow &win);
    virtual void		update() = 0;
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		pressed();
    virtual void		unPressed();
};

#endif
