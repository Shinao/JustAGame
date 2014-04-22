#include "ListItem.hh"
#include <iostream>

ListItem::ListItem(Item *item, Theme *theme, Alignment align, float scale) :
  Item(theme, align, scale),
  _selected_item(0),
  _arrow_left_focused(false),
  _arrow_right_focused(false),
  _item_theme(NULL)
{
  // Generate arrows
  _arrow_left.setPointCount(3);
  _arrow_left.setPoint(0, sf::Vector2f(0, ARROW_SIZE / 2));
  _arrow_left.setPoint(1, sf::Vector2f(ARROW_SIZE, 0));
  _arrow_left.setPoint(2, sf::Vector2f(ARROW_SIZE, ARROW_SIZE));
  _arrow_left.setFillColor(sf::Color::Black);

  _arrow_right.setPointCount(3);
  _arrow_right.setPoint(0, sf::Vector2f(0, 0));
  _arrow_right.setPoint(1, sf::Vector2f(0, ARROW_SIZE));
  _arrow_right.setPoint(2, sf::Vector2f(ARROW_SIZE, ARROW_SIZE / 2));
  _arrow_right.setFillColor(sf::Color::Black);

  add(item);
  update();
}

ListItem::~ListItem()
{
}

Item			*ListItem::getSelectedItem()
{
  return (_items[_selected_item]);
}

void			ListItem::callbackItemChanged(CallbackGui cb)
{
  _callback_item_changed = cb;
}

void			ListItem::add(Item *item)
{
  _items.push_back(item);
  item->setAlignment(Item::Alignment::Center);

  if (_item_theme != NULL)
    item->setTheme(_item_theme);
}

void			ListItem::draw(sf::RenderWindow &win)
{
  Item::draw(win);

  win.draw(_arrow_left);
  win.draw(_arrow_right);
  _items[_selected_item]->draw(win);

  sf::VertexArray lines(sf::Points, 6);
  lines[0].position = sf::Vector2f(0, 10);
  lines[1].position = sf::Vector2f(20, 0);
  lines[2].position = sf::Vector2f(20, 4);
  lines[3].position = sf::Vector2f(4, 10);
  lines[4].position = sf::Vector2f(20, 16);
  lines[5].position = sf::Vector2f(20, 20);
  for (int i = 0; i < 5; ++i)
    lines[i].color = sf::Color::Red;
  win.draw(lines);
}

void			ListItem::designChanged()
{
  Item::designChanged();

  if (_arrow_left_focused)
    _arrow_left.setFillColor(_theme->c_text_pressed);
  else if (_arrow_right_focused)
    _arrow_right.setFillColor(_theme->c_text_pressed);
  else
  {
    if (!_release && _pressed)
    {
      _arrow_left.setFillColor(_theme->c_text_focused);
      _arrow_right.setFillColor(_theme->c_text_focused);
    }
    else if (_focused)
    {
      _arrow_left.setFillColor(_theme->c_text_focused);
      _arrow_right.setFillColor(_theme->c_text_focused);
    }
    else
    {
      _arrow_left.setFillColor(_theme->c_text);
      _arrow_right.setFillColor(_theme->c_text);
    }
  }
}

void			ListItem::update()
{
  designChanged();
}

Rect			ListItem::getRectRessource() const
{
  Rect rec = _rec;

  rec.width = _items[_selected_item]->getRect().width + ARROW_SIZE * 2 + ARROW_PADDING * 2;
  return (rec);
}

void			ListItem::setRect(const Rect &rec)
{
  Item::setRect(rec);

  _arrow_left.setPosition(_rec.left + ARROW_PADDING, _rec.top + _rec.height / 2 - ARROW_SIZE / 2 + 1);
  _arrow_right.setPosition(_rec.left + _rec.width - ARROW_PADDING - ARROW_SIZE, _arrow_left.getPosition().y + 1);
  updateRectItem();
}

void			ListItem::updateRectItem()
{
  Rect rrec = getRectRessource();
  rrec.left = _rec.left + ARROW_SIZE;
  rrec.width = _rec.width - (ARROW_SIZE) * 2;
  _items[_selected_item]->setRect(rrec);
}

void			ListItem::setItemTheme(Theme *theme)
{
  _item_theme = theme;

  for (auto item : _items)
    item->setTheme(theme);
}

void		ListItem::mouseCaught(int x, int y)
{
  Item::mouseCaught(x, y);

  // Check arrows
  _items[_selected_item]->mouseCaught(x, y);
  if (_arrow_left.getGlobalBounds().contains(x, y))
  {
    _arrow_left_focused = true;
    designChanged();
  }
  else if (_arrow_right.getGlobalBounds().contains(x, y))
  {
    _arrow_right_focused = true;
    designChanged();
  }
  else
  {
    if (_arrow_right_focused || _arrow_left_focused)
    {
      _arrow_right_focused = false;
      _arrow_left_focused = false;
      designChanged();
    }
  }
}

void		ListItem::mouseLeft()
{
  _arrow_right_focused = false;
  _arrow_left_focused = false;

  Item::mouseLeft();

  _items[_selected_item]->mouseLeft();
}

void		ListItem::mouseReleased(int x, int y)
{
  Item::mouseReleased(x, y);

  // Check arrows
  if (_arrow_left.getGlobalBounds().contains(x, y))
  {
    --_selected_item;
    if (_selected_item < 0)
      _selected_item = _items.size() - 1;
    updateRectItem();
  }
  else if (_arrow_right.getGlobalBounds().contains(x, y))
  {
    ++_selected_item;
    if (_selected_item == (int) _items.size())
      _selected_item = 0;
    updateRectItem();
  }

  _items[_selected_item]->mouseReleased(x, y);
}
