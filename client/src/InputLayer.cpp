#include "InputLayer.hh"
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
  MainMenuItem("INPUT"),
  _event_catched(false)
{
  // Apply button
  String	*text = new String("Apply", jag::getTheme("Button"));
  text->autoRelease(true);
  text->addCallback(std::bind(&InputLayer::applyChanges, this));
  text->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 60, _menu->getRect().top +
	_menu->getRect().height + 8, 60, 26));
  add(text);

  _table = new Table(jag::getTheme("CenteredMenu"));

  _table->setRect(Rect(_rec.left, _y_content, _rec.width, _rec.top));
  _table->init(2);
  add(_table);


  // Generate keys
  CSimpleIniA		&ini = jag::getSettings();
  std::vector<Item *>	items;

  for (auto &key : _keys)
  {
    std::string	val = ini.GetValue(INI_GROUP, key.ini_name.c_str(), "Unknown");

    if (jag::getKeys().find(val) == jag::getKeys().end())
      val = "Unknown";
    key.sf_key = val;

    items.push_back(new String(key.label));
    items.push_back(new String(key.sf_key));
    _table->addRow(items);
    items.clear();
  }

  _table->addCallback(std::bind(&InputLayer::cbItemPressed, this), Drawable::Pressed);
}

InputLayer::~InputLayer()
{
}

void			InputLayer::mouseReleased(int x, int y)
{
  if (!_event_catched)
    Layer::mouseReleased(x, y);
}

void			InputLayer::draw(sf::RenderWindow &win)
{
  MainMenuItem::draw(win);
}

void			InputLayer::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);

  // Enable event
  _event_catched = false;
}

void			InputLayer::mouseLeft()
{
  Layer::mouseLeft();
}

void			InputLayer::applyChanges()
{
  for (auto key : _keys)
    jag::getSettings().SetValue(INI_GROUP, key.ini_name.c_str(), key.sf_key.c_str());

  jag::getSettings().SaveFile(INI_FILE);
}

bool			InputLayer::update(sf::RenderWindow &window)
{
  return (Layer::update(window));
}

int			InputLayer::eventCatched()
{
  Screen::remove(_msg_box);
  clearCallbacks();

  return (_table->getSelectedIndex());
}

void			InputLayer::cbItemPressed()
{
  // Ignore click
  if (_event_catched)
    return ;

  _msg_box = new ModalMessageBox("Input", new String("Press any key"), false);

  // Add Callback for all sf keys
  using namespace std::placeholders;
  for (auto key : jag::getKeys())
  {
    catchEvent(Action(sf::Event::MouseButtonPressed, sf::Mouse::Left), std::bind(&InputLayer::mousePressed, this, _1));
    catchEvent(Action(sf::Event::MouseButtonPressed, sf::Mouse::Right), std::bind(&InputLayer::mousePressed, this, _1));
    catchEvent(Action(sf::Event::KeyPressed, key.second), std::bind(&InputLayer::keyPressed, this, _1));
  }

  _event_catched = true;
}

void			InputLayer::keyPressed(Context context)
{
  int	index = eventCatched();

  setEventByIndex(index, jag::getValueFromEvent(context.key.code));
}

void			InputLayer::mousePressed(Context context)
{
  int	index = eventCatched();
  setEventByIndex(index, jag::getValueFromEvent(context.mouseButton.button));
}

void			InputLayer::setEventByIndex(int index, const std::string &sf_key)
{
  _keys[index].sf_key = sf_key;
  ((String *)_table->getSelectedItem(1))->setString(sf_key);
}
