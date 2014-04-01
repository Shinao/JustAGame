#ifndef LAYER_HH_
# define LAYER_HH_

# include "jag.hh"
# include "GUI/Drawable.hh"
# include "GUI/DrawableManager.hh"

// A layer is a part of a screen
// Menu - notification - titlebar - etc
// It's an abtract class - inherit from it
// For all the event - the function will return true if event is catched, meaning it will stop
// sending the event to the other layer - return false otherwise
// Manage Drawable element - Use addDrawable - clear automatically

// By default : update return false meaning the layer is not asbolute
// catchMouse return false meaning mouse function will not be called
// same thing goes for all the others event
class Layer : public DrawableManager
{
  private:
    int					_id;

  protected:
    Rect				_rec;
    bool				_focused;

  public:
    Layer();
    virtual ~Layer();

    // Event management
    virtual void		draw(sf::RenderWindow &window);
    virtual bool		update(sf::RenderWindow &window);
    virtual bool		catchMouse();
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mousePressed(int x, int y);
    virtual void		mouseReleased(int x, int y);

    // Layer properties
    void			setId(unsigned id);
    unsigned			getId() const;
    const Rect			&getRect() const;
};

#endif
