#include "GUI/Scroller.hh"

Scroller::Scroller(EventManager &event, Drawable *drawable, Theme *theme) :
  Drawable(theme),
  EventCallback(event),
  _drawable(drawable)
{
  add(drawable);
}

Scroller::~Scroller()
{
}

void			Scroller::draw(sf::RenderWindow &win)
{
  // Draw only in our area with view
  sf::View view(sf::FloatRect(_rec.left, _rec.top, _rec.width, _rec.height));
  view.setViewport(sf::FloatRect((float) _rec.left / win.getSize().x,
	(float) _rec.top / win.getSize().y, (float) _rec.width / win.getSize().x,
	(float) _rec.height / win.getSize().y));
  win.setView(view);

  DrawableManager::draw(win);

  // Restore view
  win.setView(win.getDefaultView());
}

void			Scroller::designChanged()
{
}

void			Scroller::update()
{
  designChanged();
}

void			Scroller::setRect(const Rect &rec)
{
  Drawable::setRect(rec);
}

void		Scroller::mouseCaught(int x, int y)
{
  DrawableManager::mouseCaught(x, y);
}

void		Scroller::mouseLeft()
{
  DrawableManager::mouseLeft();
}

void		Scroller::mouseReleased(int x, int y)
{
  DrawableManager::mouseReleased(x, y);
}
