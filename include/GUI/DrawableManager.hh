#ifndef DRAWABLE_MANAGER_HH_
# define DRAWABLE_MANAGER_HH_

# include "jag.hh"
# include "Drawable.hh"

// Manage Drawables
// Draw them
// Manage event when focus/click

class DrawableManager
{
  private:
    int					_id;
    bool				checkFocus(Drawable *drawable, int x, int y);

  protected:
    Drawable				*_drawable_focused;

    std::map<int, Drawable *>	_forgot_drawables;
    std::map<std::string, Drawable *>	_drawables;

  public:
    DrawableManager();
    virtual ~DrawableManager();

    // Event management
    virtual void		draw(sf::RenderWindow &window);
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);

    void				add(Drawable *drawable, std::string name);
    // Stay indefinitively - Can't get it back
    void				add(Drawable *drawable);
    Drawable				*get(std::string name);
    void				remove(std::string name);
    Drawable				*forget(std::string name);

    Drawable			*getDrawableFocused();
    void			switchDrawables(DrawableManager &manager);
};

#endif
