#include "ServerMenu.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"
#include "GUI/Table.hh"
#include "GUI/ModalMessageBox.hh"
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
  add(table, "table");

  _menu->update();

  add(_menu, "menu");

  // Network
  if (_socket.bind(5225) != sf::Socket::Done)
    new ModalMessageBox("Network", new String("Couldn't visualize the network"));

  _listener.add(_socket);
}

ServerMenu::~ServerMenu()
{
  _socket.unbind();
}

void			ServerMenu::refreshServers()
{
  if (_socket.send("ping", 5, "127.0.0.1", 25052) != sf::Socket::Done)
    new ModalMessageBox("Network", new String("Couldn't visualize the network"));
}

bool			ServerMenu::update(sf::RenderWindow &)
{
  // Check if a server is available on local
  if (!_internet)
    if (_listener.wait(sf::milliseconds(1)) &&_listener.isReady(_socket))
    {
      std::cout << "in" << std::endl;
      // Add a row to the server table
      char		buffer[1024];
      std::size_t	received = 0;
      sf::IpAddress	sender;
      unsigned short	port;

      if (_socket.receive(buffer, sizeof(buffer), received, sender, port) != sf::Socket::Done)
	return (true);

      buffer[received] = 0;
      std::cout << sender.toString() << std::endl;

      std::vector<Item *> items;
      items.push_back(new String(sender.toString()));
      ((Table *) _drawables["table"])->addRow(items);
    }

  return (true);
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
