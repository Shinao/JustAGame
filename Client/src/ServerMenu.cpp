#include "ServerMenu.hh"
#include "Screen.hh"
#include "String.hh"
#include "Table.hh"
#include "ModalMessageBox.hh"
#include "Titlebar.hh"

ServerMenu::ServerMenu() :
  Layer::Layer(),
  _internet(false)
{
  int top = jag::MarginMenu + Titlebar::HEIGHT - HEIGHT;
  Rect	rec = Rect(PADDING, top, WIDTH, Screen::getSize().y - top - 100);
  _rec = rec;
  rec.height = HEIGHT;
  _menu = new Menu(Menu::Horizontal);
  _menu->setRect(rec);
  _menu->setBorder(Border::Bottom);
  _menu->setMargin(sf::Vector2i(MARGIN, 0));

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
  table->init(1);
  add(table, "table_local");

  _menu->update();

  add(_menu, "menu");
  using namespace std::placeholders;
  Network::addRequest(Request::Allo, std::bind(&ServerMenu::serverDiscovered, this, _1));
}

ServerMenu::~ServerMenu()
{
}

void			ServerMenu::refreshServers()
{
  ProtocoledPacket	*packet = new ProtocoledPacket(NULL, Request::Allo, Network::Unconnected);

  Network::send(packet, "127.0.0.1", Network::SERVER_PORT);
}

void			ServerMenu::serverDiscovered(ProtocoledPacket &packet)
{
  std::vector<Item *>	items;
  items.push_back(new String(packet.getClient()->getIp().toString()));
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
