#include "ServerMenu.hh"
#include "Screen.hh"
#include "String.hh"
#include "ModalMessageBox.hh"
#include "Titlebar.hh"
#include "MainMenuItem.hh"
#include "LibraryLoader.hh"
#include <sstream>

ServerMenu::ServerMenu() :
  Layer::Layer(),
  _internet(false)
{
  int top = jag::MarginMenu + Titlebar::HEIGHT - MainMenuItem::HEIGHT;
  Rect	rec = Rect(MainMenuItem::PADDING, top, MainMenuItem::WIDTH, Screen::getSize().y - top - 100);
  _rec = rec;
  rec.height = MainMenuItem::HEIGHT;
  _menu = new Menu(Menu::Horizontal, jag::getTheme("HorizontalMenu"));
  _menu->setRect(rec);
  _menu->setMargin(sf::Vector2i(MainMenuItem::MARGIN, 0));

  String	*text = new String("INTERNET");
  text->addCallback([&]() { _internet = true; });
  _menu->add(text);
  text = new String("LOCAL");
  text->addCallback([&]() { _internet = false; });
  _menu->add(text);
  _menu->setPressed(text);

  text = new String("Refresh", jag::getTheme("Button"));
  text->autoRelease(true);
  text->addCallback(std::bind(&ServerMenu::refreshServers, this));
  text->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 60, _menu->getRect().top +
	_menu->getRect().height + 8, 60, 26));
  add(text);

  _table = new Table(4);
  Rect rec_btn = text->getRect();
  int		top_table = rec_btn.top + rec_btn.height + 8;

  _table->setRect(Rect(_rec.left, top_table, _rec.width, _rec.height - top_table));
  using namespace std::placeholders;
  _table->addItemsCallback(std::bind(&ServerMenu::serverSelected, this), Drawable::Pressed);
  add(_table, "table");

  _menu->update();

  add(_menu, "menu");

  // TODO - Remove
  std::vector<Item *>	items;
  items.push_back(new String("Private"));
  items.push_back(new String("TestServer"));
  items.push_back(new String("TicTacToe"));
  items.push_back(new String("0/2"));
  _table->addRow(items);
  items.clear();
  items.push_back(new String("Public"));
  items.push_back(new String("OBlaalall aalla"));
  items.push_back(new String("Nope"));
  items.push_back(new String("10/20"));
  _table->addRow(items);
}

ServerMenu::~ServerMenu()
{
}

void			ServerMenu::refreshServers()
{
  using namespace std::placeholders;
  Network::askForServer(std::bind(&ServerMenu::serverDiscovered, this, _1));
}

void			ServerMenu::serverDiscovered(ProtocoledPacket &packet)
{
  std::vector<Item *>	items;
  std::stringstream	ss;

  std::string	name;
  std::string	game_mode;
  bool		has_password;
  sf::Uint8	nb_players;
  sf::Uint8	max_players;

  packet >> name >> game_mode >> has_password >> nb_players >> max_players;
  ss << nb_players << "/" << max_players;

  items.push_back(new String(has_password ? "Private" : "Public"));
  items.push_back(new String(name));
  items.push_back(new String(game_mode));
  items.push_back(new String(ss.str()));
  _table->addRow(items);
}

void			ServerMenu::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);

  Screen::setMoving(false);
}

void			ServerMenu::mousePressed(int x, int y)
{
  Layer::mousePressed(x, y);

  if (getDrawableFocused() == NULL)
    Screen::setMoving(true);
}

void			ServerMenu::serverSelected()
{
  Item	*item = _table->getSelectedItem(0);

  // Get Library from game name and load it
  // LibraryLoader	lib(game_mode, "Games/");
  // if (!lib.open())
  //   return (error("Could not open library : " + lib.getFullPath()));
}
