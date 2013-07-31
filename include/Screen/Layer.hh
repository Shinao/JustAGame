#ifndef LAYER_HH_
# define LAYER_HH_

# include <SFML/Graphics.hpp>

// A layer is a part of a screen
// Menu - notification - titlebar - etc
// It's an abtract class - inherit from it
// For all the event - the function will return
// true if event is catched, meaning it will stop
// sending the event to the other layer - return
// false otherwise

class Layer
{
  protected:
    int				_x;
    int				_y;
    int				_height;
    int				_width;
    int				_id;

  public:
    Layer();
    virtual ~Layer();

    // Event management
    virtual bool		update(sf::RenderWindow &window) = 0;
    virtual void		mouseMoved(int x, int y);
    virtual void		mouseLeft();
    virtual bool		catchEvent(sf::Event &event);
    virtual bool		textEntered();

    // Layer properties
    void			setId(unsigned id);
    unsigned			getId() const;
    int				getX() const;
    int				getY() const;
    int				getHeight() const;
    int				getWidth() const;
};

#endif
