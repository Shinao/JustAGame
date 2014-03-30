#include "GUI/ListBox.hh"
#include <iostream>

ListBox::ListBox(EventManager &event, Item *button, Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale),
  EventCallback(event),
  _button(button),
  _is_open(false),
  _selected_item(NULL)
{
  DrawableManager::add(button, "button");
  button->addCallback([&]() { toggle(); });
  button->autoRelease(true);
  button->setTheme(theme);
  button->setAlignment(Item::Alignment::Center);

  // Menu that we will toggle
  _menu = new Menu(Menu::Vertical, Rect(0, 0, 0, 0));
  _menu->setMargin(sf::Vector2i(6, 6));
  _menu->shrinkToFit(true);
}

ListBox::~ListBox()
{
}

bool			ListBox::isOpen()
{
  return (_is_open);
}

void			ListBox::toggle()
{
  _is_open = !_is_open;

  if (_is_open)
  {
    // Fix Event Released button automatic close menu
    _patch_has_moved = false;

    DrawableManager::add(_menu, "menu");

    // Mouse event by EventManager since we have a popup
    using namespace std::placeholders;
    catchEvent(Action(sf::Event::MouseMoved), [&](Context context) { 
	_patch_has_moved = true;
	if (_menu->getRect().contains(context.mouseMove.x, context.mouseMove.y))
	_menu->mouseCaught(context.mouseMove.x, context.mouseMove.y);
	else
	_menu->mouseLeft();
	});

    catchEvent(Action(sf::Event::MouseButtonReleased, sf::Mouse::Left), [&](Context context) {
	if (!_patch_has_moved)
	return ;

	if (_menu->getRect().contains(context.mouseButton.x, context.mouseButton.y));
	else
	toggle();
	});
  }
  else
  {
    DrawableManager::forget("menu");

    // Clear callbacks
    EventCallback::clearCallbacks();
  }
}

void			ListBox::add(Item *item)
{
  _menu->add(item);
  _menu->update();
}

void			ListBox::draw(sf::RenderWindow &win)
{
  Item::draw(win);
  DrawableManager::draw(win);
}

void			ListBox::designChanged()
{
  Item::designChanged();

  if (!_release && _pressed)
  {
  }
  else if (_focused)
  {
  }
  else
  {
  }
}

void			ListBox::update()
{
  _menu->update();
  _button->update();

  designChanged();
}

Rect			ListBox::getRectRessource() const
{
  return (_button->getRectRessource());
}

void			ListBox::setRect(const Rect &rec)
{
  Item::setRect(rec);

  _button->setRect(rec);
  _menu->setRect(Rect(rec.left, rec.top + rec.height, rec.width, _menu->getRect().height));
}



//
// Same event inherited : Share it !
//
void		ListBox::mouseCaught(int x, int y)
{
  DrawableManager::mouseCaught(x, y);
  Item::mouseCaught(x, y);
}

void		ListBox::mouseLeft()
{
  DrawableManager::mouseLeft();
  Item::mouseLeft();
}

void		ListBox::mouseReleased(int x, int y)
{
  DrawableManager::mouseReleased(x, y);
  Item::mouseReleased(x, y);
}
