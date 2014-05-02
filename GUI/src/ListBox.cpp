#include "ListBox.hh"
#include <iostream>

ListBox::ListBox(String *button, Theme *theme, float scale) :
  Item(theme, scale),
  EventCallback(),
  _button(button),
  _is_open(false),
  _selected_item(NULL),
  _item_theme(jag::getTheme("ItemListBox"))
{
  DrawableManager::add(button);
  button->addCallback([&]() { toggle(); });
  button->setTheme(theme);

  // Menu that we will toggle
  _menu = new Menu(Menu::Vertical, theme);
  _menu->setMargin(sf::Vector2i(6, 6));
  _menu->shrinkToFit(true);

  _scroller = new Scroller(_menu);
}

ListBox::~ListBox()
{
  // DrawableManager doesnt contain menu if closed
  if (!_is_open)
    delete _scroller;
}

bool			ListBox::isOpen()
{
  return (_is_open);
}

Item			*ListBox::getSelectedItem()
{
  return (_selected_item);
}

void			ListBox::toggle()
{
  _is_open = !_is_open;

  if (_is_open)
  {
    // Fix Event Released button automatic close menu
    _patch_has_moved = false;

    DrawableManager::add(_scroller, "scroller");

    // Mouse event by EventManager since we have a popup
    using namespace std::placeholders;
    catchEvent(Action(sf::Event::MouseMoved), [&](Context context) { 
	_patch_has_moved = true;
	if (_scroller->getRect().contains(context.mouseMove.x, context.mouseMove.y))
	_scroller->mouseCaught(context.mouseMove.x, context.mouseMove.y);
	else
	_scroller->mouseLeft();
	});

    catchEvent(Action(sf::Event::MouseButtonReleased, sf::Mouse::Left), [&](Context context) {
	if (!_patch_has_moved)
	  return ;

	if (_scroller->getRect().contains(context.mouseButton.x, context.mouseButton.y))
	  _scroller->mouseReleased(context.mouseButton.x, context.mouseButton.y);

	toggle();
	});
  }
  else
  {
    DrawableManager::forget("scroller");
    released();

    // Clear callbacks
    EventCallback::clearCallbacks();
  }
}

void			ListBox::released()
{
  Item::released();

  _button->released();
}

void			ListBox::callbackItemChanged(CallbackGui cb)
{
  _callback_item_changed = cb;
}

void			ListBox::setItemTheme(Theme *theme)
{
  _item_theme = theme;
}

void			ListBox::add(String *item)
{
  _menu->add(item);
  item->setTheme(_item_theme);
  _menu->update();

  // Add callback Item to redirect to the listbox item changed
  item->addCallback([&, item]() {
      if (item == _selected_item)
        return ;

      _selected_item = item;
      _button->setString(item->getString());

      if (_callback_item_changed)
        _callback_item_changed();
  });
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

  Rect scroller_rec = Rect(rec.left, rec.top + rec.height + _theme->size_border,
      rec.width, 50);
  _scroller->setRect(scroller_rec);
  scroller_rec.height = _menu->getRect().height;
  _menu->setRect(scroller_rec);
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
