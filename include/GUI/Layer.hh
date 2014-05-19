#ifndef LAYER_HH_
# define LAYER_HH_

# include "jag.hh"
# include "DrawableManager.hh"

// A layer is a part of a screen
// Menu - notification - titlebar - etc
// It's an abtract class - inherit from it
// Return true or false for catchMouse if you want to get the mouse event
// Update return true : sending the event to the other layer - return false otherwise
// Manage Drawable element - Use addDrawable - clear automatically

// By default : update return false meaning the layer is not asbolute
// catchMouse return true meaning mouse function will be called

class Layer : public DrawableManager
{
  private:
    int					_id;

  protected:
    Rect				_rec;
    bool				_focused;

  public:
    enum			Type
    {
      Game,
      Setting,
      Other
    }				_type;

    Layer(Type type = Game);
    virtual ~Layer();

    // Event management
    virtual void		draw(sf::RenderWindow &window);
    virtual bool		update(sf::RenderWindow &window);
    virtual bool		catchMouse() const;
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mousePressed(int x, int y);
    virtual void		mouseReleased(int x, int y);

    // Layer properties
    void			setId(unsigned id);
    unsigned			getId() const;
    const Rect			&getRect() const;
    Type			getType() const;
};

#endif
