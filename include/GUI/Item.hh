#ifndef ITEM_HH_
# define ITEM_HH_

# include "GUI/jag.hh"
# include "GUI/Drawable.hh"

// Abstract class item for text & sprite
// Object depending on a menu
// Item should always have a theme
// Item has an ID useful for the getPressed and Focused function of the menu

class Item : public Drawable
{
  protected:
    float			_scale;
    sf::Vector2i		_margin;
    sf::RectangleShape		_box;
    sf::RectangleShape		_border;

  public:
    Item(Theme *theme = jag::getCurrentTheme(), float scale = 1.0f);
    virtual ~Item();

    const sf::Vector2i		&getMargin() const;
    void			setMargin(const sf::Vector2i &margin);
    Rect			getRect() const;
    virtual void		setRect(const Rect &rec);
    sf::Vector2i		getRessourcePosition();
    void			setBorder(Border::Type border);

    virtual Rect		getRectRessource() const = 0;
    virtual void		draw(sf::RenderWindow &win);
    virtual void		update() = 0;
    virtual void		mouseReleased(int x, int y);
    virtual void		released();
    virtual void		designChanged();
};

#endif
