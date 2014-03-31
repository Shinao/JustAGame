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
  // Draw only in our area with View
  sf::View view(sf::FloatRect(_rec.left, _rec.top, _rec.width, _rec.height));
  view.setViewport(sf::FloatRect((float) _rec.left / win.getSize().x,
	(float) _rec.top / win.getSize().y, (float) _rec.width / win.getSize().x,
	(float) _rec.height / win.getSize().y));
  win.setView(view);

  DrawableManager::draw(win);
  win.draw(_scroll_box);

  // Restore view
  win.setView(win.getDefaultView());
}

void			Scroller::designChanged()
{
  sf::Color color = _theme->c_border_pressed;
  color.a = 100;
  _scroll_box.setFillColor(color);
}

void			Scroller::update()
{
  designChanged();
}

void			Scroller::setRect(const Rect &rec)
{
  Drawable::setRect(rec);

  // Set position and size of scroll box
  _scroll_box.setPosition(rec.left + rec.width - jag::ScrollerSize, rec.top);
  // Set size by content showing proportion
  _scroll_box.setSize(sf::Vector2f(jag::ScrollerSize, (float) rec.height / _drawable->getRect().height * rec.height));
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
