#include "Scroller.hh"
#include <iostream>

Scroller::Scroller(Drawable *drawable, Theme *theme) :
  Drawable(theme),
  EventCallback(),
  _drawable(drawable)
{
  add(drawable);
}

Scroller::~Scroller()
{
}

void			Scroller::checkOutOfBounds(int delta)
{
  if (delta < 0)
  {
    bool out = _drawable->getRect().top + _drawable->getRect().height < _rec.top + _rec.height;

    if (out)
    {
      _scroll_box.setPosition(_scroll_box.getPosition().x, _rec.top + _rec.height - _scroll_box.getSize().y);
      _drawable->setRect(Rect(_drawable->getRect().left, _rec.top + _rec.height - _drawable->getRect().height, _drawable->getRect().width, _drawable->getRect().height));
    }
  }
  else
  {
    bool out = _drawable->getRect().top > _rec.top;

    if (out)
    {
      _scroll_box.setPosition(_scroll_box.getPosition().x, _rec.top);
      _drawable->setRect(Rect(_drawable->getRect().left, _rec.top, _drawable->getRect().width, _drawable->getRect().height));
    }
  }
}

void			Scroller::draw(sf::RenderWindow &win)
{
  // Define drawing area
  Screen::scissor(_rec);

  DrawableManager::draw(win);
  win.draw(_scroll_box);

  // Restore view
  Screen::undoScissor();
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
  _scroll_box.setPosition(rec.left + rec.width - SCROLLER_SIZE, rec.top);
  // Set size by content showing proportion
  _scroll_box.setSize(sf::Vector2f(SCROLLER_SIZE, (float) rec.height / _drawable->getRect().height * rec.height));
}

void		Scroller::mouseCaught(int x, int y)
{
  if (!_focused)
    catchEvent(Action(sf::Event::MouseWheelMoved), [&](Context context) {
	// MouseCaught - Simulate as if our mouse moved
	mouseCaught(context.mouseWheel.x, context.mouseWheel.y);

	int add_drawable = context.mouseWheel.delta * SCROLLING;
	int add_scroll = context.mouseWheel.delta * ((float) SCROLLING / _drawable->getRect().height * _rec.height);

	_scroll_box.setPosition(_scroll_box.getPosition().x, _scroll_box.getPosition().y - add_scroll);
	_drawable->setRect(Rect(_drawable->getRect().left, _drawable->getRect().top + add_drawable, 
	    _drawable->getRect().width, _drawable->getRect().height)); 

	// Avoid out-of-bounds
	checkOutOfBounds(context.mouseWheel.delta);
	});

  Drawable::mouseCaught(x, y);
  DrawableManager::mouseCaught(x, y);
}

void		Scroller::mouseLeft()
{
  Drawable::mouseLeft();
  DrawableManager::mouseLeft();

  clearCallbacks();
}

void		Scroller::mouseReleased(int x, int y)
{
  Drawable::mouseReleased(x, y);
  DrawableManager::mouseReleased(x, y);
}
