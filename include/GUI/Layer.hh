#ifndef LAYER_HH_
# define LAYER_HH_

# include "jag.hh"

class Screen;

// A layer is a part of a screen
// Menu - notification - titlebar - etc
// It's an abtract class - inherit from it
// For all the event - the function will return true if event is catched, meaning it will stop
// sending the event to the other layer - return false otherwise

// Only draw must be implemented
// By default : update return false meaning the layer is not asbolute
// catchMouse return false meaning mouse function will not be called
// same thing goes for all the others event
class Layer
{
  private:
    int				_id;

  protected:
    Screen			&_screen;
    Rect			_rec;
    bool			_focused;

  public:
    Layer(Screen &screen);
    virtual ~Layer();

    // Event management
    virtual void		draw(sf::RenderWindow &window) = 0;
    virtual bool		update(sf::RenderWindow &window);
    virtual bool		catchMouse();
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		pressed(int x, int y);
    virtual void		released(int x, int y);

    // Layer properties
    void			setId(unsigned id);
    unsigned			getId() const;
    const Rect			&getRect() const;
};

#endif
