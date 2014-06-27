#include "Container.hh"

Container::Container(Theme *theme) :
  Drawable(theme)
{
}

Container::~Container()
{
}


void			Container::draw(sf::RenderWindow &win)
{
  Drawable::draw(win);
}

void			Container::update()
{
}

void			Container::designChanged()
{
}
