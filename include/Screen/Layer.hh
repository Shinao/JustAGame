#ifndef LAYER_HH_
# define LAYER_HH_

# include <SFML/Graphics.hpp>
# include <iostream>

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
    std::vector<int>		_actions;
    int				_id;

  protected:
    int				_x;
    int				_y;
    int				_height;
    int				_width;

    int				actionId();

  public:
    Layer();
    virtual ~Layer();

    // Event management
    virtual void		draw(sf::RenderWindow &window) = 0;
    virtual bool		update(sf::RenderWindow &window);
    virtual bool		catchMouse();
    virtual void		mouseMoved(int x, int y);
    virtual void		mouseLeft();
    virtual bool		textEntered(sf::Uint32 unicode);

    // Layer properties
    void			setId(unsigned id);
    unsigned			getId() const;
    int				getX() const;
    int				getY() const;
    int				getHeight() const;
    int				getWidth() const;
};

#endif
