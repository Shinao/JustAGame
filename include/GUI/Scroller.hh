#ifndef SCROLLER_HH_
# define SCROLLER_HH_

# include "GUI/Drawable.hh"
# include "GUI/DrawableManager.hh"
# include "EventCallback.hh"

// Scroller : show partially a drawable

class Scroller : public Drawable, public DrawableManager, public EventCallback
{
  private:
    Drawable			*_drawable;

  public:
    Scroller(EventManager &event, Drawable *drawable, Theme *theme = jag::getCurrentTheme());
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
