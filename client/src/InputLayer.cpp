#include "InputLayer.hh"
#include "Table.hh"
#include "jag.hh"
#include <iostream>

// Generate keys
InputLayer::Keys	InputLayer::_keys[NB_INPUT] = {
  {"key_fire", "FIRE", "Unknown"},
  {"key_secondary_fire", "SECONDARY FIRE", "Unknown"},
  {"key_up", "UP", "Unknown"},
  {"key_left", "LEFT", "Unknown"},
  {"key_right", "RIGHT", "Unknown"},
  {"key_down", "DOWN", "Unknown"},
  {"key_escape", "ESCAPE", "Unknown"}
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


  // Generate keys
  CSimpleIniA		&ini = jag::getSettings();
  std::vector<Item *>	items;

  for (auto key : _keys)
  {
    std::string	val = ini.GetValue(INI_GROUP, key.ini_name.c_str(), "Unknown");

    if (jag::getKeys().find(val) == jag::getKeys().end())
      val = "Unknown";
    key.sf_key = val;

    items.push_back(new String(key.label));
    items.push_back(new String(key.sf_key));
    table->addRow(items);
    items.clear();
  }
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
  jag::getSettings().SaveFile(INI_FILE);
}
