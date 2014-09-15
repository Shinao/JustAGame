#ifndef CONTAINER_HH_
# define CONTAINER_HH_

# include "GUI/Item.hh"
# include "GUI/EventManager.hh"
# include "GUI/EventCallback.hh"

#include <iostream>

// Container : empty drawable

class Container : public Drawable
{
  public:
    Container(Theme *theme = jag::getCurrentTheme());
    ~Container();

    void			draw(sf::RenderWindow &win);
    void			update();
    void			designChanged();
};

#endif
