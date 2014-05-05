#include "InputLayer.hh"
#include "Table.hh"
#include "jag.hh"

// Generate keys
InputLayer::Keys	InputLayer::_keys[NB_INPUT] = {
  {"key_up", "UP", sf::Keyboard::A},
  {"key_left", "LEFT", sf::Keyboard::A},
  {"key_right", "RIGHT", sf::Keyboard::A},
  {"key_down", "DOWN", sf::Keyboard::A},
  {"key_escape", "ESCAPE", sf::Keyboard::A}
};

InputLayer::InputLayer() :
  MainMenuItem("INPUT")
{
  // Apply button
  String	*text = new String("Apply", jag::getTheme("Button"));
  text->autoRelease(true);
  text->addCallback(std::bind(&InputLayer::applyChanges, this));
  text->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 60, _menu->getRect().top +
	_menu->getRect().height + 8, 60, 26));
  add(text);

  Table		*table = new Table(jag::getTheme("CenteredMenu"));

  table->setRect(Rect(_rec.left, _y_content, _rec.width, _rec.top));
  table->init(2);
  add(table, "table");

  std::vector<Item *>	items;
  items.push_back(new String("teeest"));
  items.push_back(new String("DASDASD"));
  table->addRow(items);
}

InputLayer::~InputLayer()
{
}

void			InputLayer::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			InputLayer::draw(sf::RenderWindow &win)
{
  MainMenuItem::draw(win);
}

void			InputLayer::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}

void			InputLayer::mouseLeft()
{
  Layer::mouseLeft();
}

void			InputLayer::applyChanges()
{
}
