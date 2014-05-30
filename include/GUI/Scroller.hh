#ifndef SCROLLER_HH_
# define SCROLLER_HH_

# include "Screen.hh"
# include "Drawable.hh"
# include "DrawableManager.hh"
# include "EventCallback.hh"

// Scroller : show partially a drawable

class Scroller : public Drawable, public DrawableManager, public EventCallback
{
  private:
    static const int		SCROLLER_SIZE = 8;
    static const int		SCROLLING = 16;

    Drawable			*_drawable;
    sf::RectangleShape		_scroll_box;

    void			checkOutOfBounds(int delta);

  public:
    Scroller(Drawable *drawable, Theme *theme = jag::getCurrentTheme());
    ~Scroller();

    void			setRect(const Rect &rec);
    void			draw(sf::RenderWindow &win);
    void			update();
    void			designChanged();

    // Event
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);
};

#endif
