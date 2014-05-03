#include "ServerMenu.hh"
#include "Screen.hh"
#include "String.hh"
#include "Table.hh"
#include "ModalMessageBox.hh"
#include "Titlebar.hh"
#include "MainMenuItem.hh"
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

  Table		*table = new Table();
  Rect rec_btn = text->getRect();
  int		top_table = rec_btn.top + rec_btn.height + 8;

  table->setRect(Rect(_rec.left, top_table, _rec.width, _rec.height - top_table));
  table->init(4);
  add(table, "table_local");

  _menu->update();

  add(_menu, "menu");
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
  ((Table *) _drawables["table_local"])->addRow(items);
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
