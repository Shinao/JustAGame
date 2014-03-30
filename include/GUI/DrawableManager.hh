#ifndef DRAWABLE_MANAGER_HH_
# define DRAWABLE_MANAGER_HH_

# include "jag.hh"
# include "GUI/Drawable.hh"

// Manage Drawables
// Draw them
// Manage event when focus/click

class DrawableManager
{
  protected:
    Drawable				*_drawable_focused;

    std::map<std::string, Drawable *>	_drawables;
    void				addDrawable(Drawable *drawable, std::string name);
    Drawable				*getDrawable(std::string name);

  public:
    DrawableManager();
    virtual ~DrawableManager();

    // Event management
    virtual void		draw(sf::RenderWindow &window);
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);
};

#endif

