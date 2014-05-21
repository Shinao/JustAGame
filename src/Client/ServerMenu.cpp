# include "AGameClient.hh"
#include "ServerMenu.hh"
#include "Screen.hh"
#include "String.hh"
#include "Titlebar.hh"
#include <sstream>
#include <fstream>

AGameClient			*_game;
using namespace std::placeholders;

ServerMenu::ServerMenu() :
  MainMenuItem("INTERNET"),
  _internet(false),
  _state(Unconnected),
  _server(NULL)
{
  String	*text = new String("LOCAL");
  text->addCallback([&]() { _internet = false; });
  _menu->add(text);
  _menu->setPressed(text);
  _title->addCallback([&]() { _internet = true; });

  text = new String("Refresh", jag::getTheme("Button"));
  text->autoRelease(true);
  text->addCallback(std::bind(&ServerMenu::refreshServers, this));
  add(text, "refresh");

  _table = new Table(4);

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

  // Manage server connexion and disconnexion
  Network::addRequest(Request::Connexion, std::bind(&ServerMenu::connectedToServer, this, _1));
  Network::addRequest(Request::Disconnexion, std::bind(&ServerMenu::couldNotConnect, this, _1));

  settingChanged();
}

ServerMenu::~ServerMenu()
{
}

void			ServerMenu::refreshServers()
{
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
  ss << (int) nb_players << "/" << (int) max_players;

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
  // User notification
  _msg = new ModalMessageBox("Connexion", new String("Trying to connect to server..."));
  _msg->addExitCallback(std::bind(&ServerMenu::tryingToEscape, this));
  _msg->addButton("Cancel");

  // Connect to server
  // Item	*item = _table->getSelectedItem(0);

  // TODO - Not brute - get info via table
  Client *client = new Client();
  client->setIp("127.0.0.1");
  client->setPort(Network::SERVER_PORT);

  _thread = Network::connect(client);
  _state = Connecting;
}

void			ServerMenu::couldNotConnect(ProtocoledPacket &)
{
  delete _thread;

  // User aborted operation
  if (_state != Connecting)
  {
    Screen::remove(_msg);
    return ;
  }

  connectionError("Could not connect to server (Timeout)");
}

void			ServerMenu::connectedToServer(ProtocoledPacket &packet)
{
  delete _thread;

  // User aborted operation
  if (_state != Connecting)
  {
    Screen::remove(_msg);
    return ;
  }

  _state = Connected;
  // Setting server
  _server = packet.getClient();

  // Checking our library
  _game_mode = "TicTacToe";
  std::string	lib_name = _game_mode + Network::SUFFIX_CLIENT;

  // Get Library from game name and download it if fail
  _lib = new LibraryLoader(lib_name, Network::GAMES_PATH + _game_mode + "/");
  if (!_lib->open())
  {
    _msg->setDescription(new String("Game not found - Asking server"));
    ProtocoledPacket *get_game = new ProtocoledPacket(_server, Request::GetGame, Network::TCP);
    *get_game << ((LibraryLoader::getPlateform() == LibraryLoader::Win32) ? true : false);
    Network::send(get_game);
    Network::addRequest(Request::GetGame, std::bind(&ServerMenu::getGame, this, _1));
    return ;
  }

  launchGame();
}

void			ServerMenu::getGame(ProtocoledPacket &packet)
{
  // User aborted operation
  if (_state != Connected)
    return ;

  // Get info file
  std::string	filename;
  sf::Int8	progress;
  sf::Int32	nb_bytes;
  packet >> filename >> progress >> nb_bytes;

  // Check if can't get the library
  if (progress < 0)
  {
    connectionError("Could not download " + filename);
    return ;
  }
  // We have our files !
  if (nb_bytes == 0)
  {
    if (!_lib->open())
      connectionError("Could not load the game, that's strange.");
    else
      launchGame();
    return ;
  }

  // Append to our file
  // We open it and append then close it - We should probably keep the handle but... lazy
  std::ofstream	file;
  file.open(filename, std::ios_base::app);
  if (!file.is_open())
  {
    connectionError("Could not open " + filename);
    return ;
  }

  file.write(&((char *) packet.getData())[packet.getDataSize() - nb_bytes], nb_bytes);
  file.close();
}

void			ServerMenu::connectionError(const std::string &desc)
{
  _msg->setDescription(new String(desc));
  _msg->clearButtons();
  _msg->addButton("Back");

  _server = NULL;
  _state = Unconnected;
}

void			ServerMenu::launchGame()
{
  _msg->setDescription(new String("Loading the game..."));

  // Get the game
  typedef AGameClient *(*f_getGame)();
  f_getGame	func_ptr = (f_getGame) _lib->getFunction("getGame");
  if (func_ptr == NULL)
  {
    connectionError("Library corrupted : " + _lib->getFullPath());
    return ;
  }

  _game = func_ptr();
  _game->setServer(_server);
  if (!_game->init())
  {
    connectionError("Could not init the game - Check " INI_FILE);
    return ;
  }

  Network::addRequest(Request::InitGame, std::bind(&ServerMenu::initGame, this, _1));
}

void			ServerMenu::initGame(ProtocoledPacket &packet)
{
  _msg->setDescription(new String("Getting information from the server..."));

  if (!_game->initGame(packet))
    return ;

  _game->run();

  Screen::removeFromSetting(_msg);
  Network::removeRequest(Request::GetGame);
  Network::removeRequest(Request::InitGame);
}

// User Canceled or used Escape
bool			ServerMenu::tryingToEscape()
{
  // Already aborting
  if (_state == Aborting)
    return (false);

  Network::removeRequest(Request::GetGame);
  Network::removeRequest(Request::InitGame);

  // There has been an error so we can exit
  if (_state == Unconnected)
    return (true);

  // Close connection - TODO : Use Network::disconnect
  if (_state == Connected)
    _server->getSocket().disconnect();

  // Aborting
  _msg->setDescription(new String("Aborting connection..."));
  _msg->getButton(0)->setState(Drawable::Pressed);

  _state = Aborting;
  _server = NULL;

  return (false);
}

void			ServerMenu::settingChanged()
{
  MainMenuItem::settingChanged();

  _drawables["refresh"]->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 60, _menu->getRect().top + _menu->getRect().height + 8, 60, 26));

  Rect rec_btn = _drawables["refresh"]->getRect();
  int		top_table = rec_btn.top + rec_btn.height + 8;

  _table->setRect(Rect(_rec.left, top_table, _rec.width, _rec.height - top_table));
}
