#include "Client/ServerMenu.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"
#include "Client/Titlebar.hh"
#include "GUI/GameManager.hh"
#include "System/System.hh"
#include <sstream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std::placeholders;

ServerMenu::ServerMenu() :
  MainMenuItem("INTERNET"),
  _state(Unconnected),
  _internet(false),
  _game(NULL)
{
  serverSelected();

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
}

ServerMenu::~ServerMenu()
{
}

void			ServerMenu::settingChanged()
{
  MainMenuItem::settingChanged();

  _drawables["refresh"]->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 60, _menu->getRect().top + _menu->getRect().height + 8, 60, 26));

  Rect rec_btn = _drawables["refresh"]->getRect();
  int		top_table = rec_btn.top + rec_btn.height + 8;

  _table->setRect(Rect(_rec.left, top_table, _rec.width, _rec.height - top_table));
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
  _msg = new ModalMessageBox("Connexion", new String(""));
  _msg->addExitCallback(std::bind(&ServerMenu::tryingToEscape, this));

  if (GameManager::isRunning())
  {
    _msg->setDescription(new String("Disconnecting from current server..."));

    GameManager::exitGame();
    Network::addRequest(Request::Disconnexion, std::bind(&ServerMenu::disconnectedFromGame, this, _1));
    _state = Disconnecting;

    return ;
  }

  connectToServer();
}

void			ServerMenu::connectToServer()
{
  // Manage server connexion and disconnexion
  Network::addRequest(Request::Connexion, std::bind(&ServerMenu::connectedToServer, this, _1));
  Network::addRequest(Request::Disconnexion, std::bind(&ServerMenu::couldNotConnect, this, _1));

  // User notification
  _msg->canEscape(true);
  _msg->setDescription(new String("Trying to connect to server..."));
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

  _state = Unconnected;
  connectionError("Could not connect to server (Timeout)");
}

// We were disconnecting from the current running game
void			ServerMenu::disconnectedFromGame(ProtocoledPacket &)
{
  Network::removeRequest(Request::Disconnexion);
  // TODO - Remove ?
  connectToServer();
}

void			ServerMenu::abortConnexion(ProtocoledPacket &packet)
{
  delete _thread;

  // Setting server
  _server = packet.getClient();

  Network::removeRequest(Request::Disconnexion);
  Network::addRequest(Request::Disconnexion, std::bind(&ServerMenu::abortDisconnexion, this, _1));
  Network::disconnect(_server);
}

void			ServerMenu::abortDisconnexion(ProtocoledPacket &)
{
  Screen::remove(_msg);
}

// User aborted operation
void			ServerMenu::abortCouldNotConnect(ProtocoledPacket &)
{
  delete _thread;

  Network::removeRequest(Request::Connexion);
  Network::removeRequest(Request::Disconnexion);
  Screen::remove(_msg);
}

void			ServerMenu::connectionError(const std::string &desc)
{
  _msg->setTitle("Error");
  _msg->setDescription(new String(desc));
  _msg->clearButtons();
  _msg->addButton("Back");

  _state = Unconnected;
}

void			ServerMenu::connectedToServer(ProtocoledPacket &packet)
{
  delete _thread;

  // Setting server
  _server = packet.getClient();

  // User aborted operation
  if (_state != Connecting)
    return ;

  _state = Connected;

  Network::addRequest(Request::ServerInfo, std::bind(&ServerMenu::getInfo, this, _1));
}

void			ServerMenu::getInfo(ProtocoledPacket &packet)
{
  std::string	server;
  bool		has_password;

  packet >> server >> _game_mode >> _version >> has_password;

  std::cout << server << " :: " << _game_mode << " [" << (int) _version << "]" << std::endl;

  // Checking our library
  std::string	lib_name = _game_mode + Network::SUFFIX_CLIENT;

  // Get Library from game name and download it if fail
  _lib = new LibraryLoader(lib_name, Network::GAMES_PATH + _game_mode + "/");
  if (!_lib->open())
    incorrectVersion();
  else
    launchGame();
}

void			ServerMenu::incorrectVersion()
{
  _msg->setTitle("Downloading");
  _msg->setDescription(new String("Game not found - Asking server"));

  Network::addRequest(Request::GetGame, std::bind(&ServerMenu::getGame, this, _1));
  ProtocoledPacket *get_game = new ProtocoledPacket(_server, Request::GetGame, Network::TCP);
  *get_game << ((System::getOS() == System::Win32) ? true : false);
  Network::send(get_game);

  // Create repositories
  System::createDirectory(Network::GAMES_PATH);
  System::createDirectory(Network::GAMES_PATH + _game_mode);
  System::createDirectory(Network::GAMES_PATH + _game_mode + "/" + Network::RSRC_PATH);

  // Remove files if already here
  System::removeFile(_lib->getFullPath());
  System::removeFile(Network::GAMES_PATH + _game_mode + "/" + Network::RSRC_PATH + "/*");

  std::vector<System::File *>	*list = System::getFiles(Network::GAMES_PATH + _game_mode + "/" + Network::RSRC_PATH);
  for (auto file : *list)
    if (file->type == System::File::FileType)
      System::removeFile(Network::GAMES_PATH + _game_mode + "/" + Network::RSRC_PATH + file->name);

  for (auto file : *list)
    delete file;
  delete list;
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
  std::string	min_filename = filename;
  size_t	pos;

  if ((pos = min_filename.find_last_of('/')) != std::string::npos)
    min_filename = min_filename.substr(pos + 1);

  // Check if can't get the library
  if (progress < 0)
  {
    connectionError("Could not download " + min_filename);
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
  std::ofstream	file;
  file.open(filename, std::ios_base::binary | std::ios_base::app);
  if (!file.is_open())
  {
    connectionError("Could not open " + min_filename);
    return ;
  }

  file.write(&((char *) packet.getData())[packet.getDataSize() - nb_bytes], nb_bytes);
  file.close();

  std::stringstream	ss;
  ss  << min_filename << "\n[";
  for (int i = 0; i < 100; ++i)
    if ((float) progress / 100 * 100 > i)
      ss << "|";
    else
      ss << " ";
  ss << "]\ndasdd\ndasd\ndasdasd\ndsad";
  _msg->setDescription(new String(ss.str()));
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

  // Checking if incorrect version
  if (_version != _game->getVersion())
  {
    delete _game;
    _lib->free();
    incorrectVersion();
    return ;
  }

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

  Screen::remove(_msg);
  Network::removeRequest(Request::GetGame);
  Network::removeRequest(Request::InitGame);
  Network::removeRequest(Request::Connexion);
  Network::removeRequest(Request::Disconnexion);

  if (GameManager::isRunning())
    GameManager::exitGame();

  GameManager::runGame(_game);
}

// User Canceled or used Escape
bool			ServerMenu::tryingToEscape()
{
  // Already aborting
  if (_state == Aborting || _state == Disconnecting)
    return (false);

  Network::removeRequest(Request::GetGame);
  Network::removeRequest(Request::InitGame);
  Network::removeRequest(Request::Disconnexion);
  Network::removeRequest(Request::Connexion);

  // Could not connect to server - User pressed OK
  if (_state == Unconnected)
    return (true);

  if (_state == Connected)
  {
    Network::disconnect(_server, false);
    Network::addRequest(Request::Disconnexion, std::bind(&ServerMenu::abortDisconnexion, this, _1));
  }
  else
    Network::addRequest(Request::Disconnexion, std::bind(&ServerMenu::abortCouldNotConnect, this, _1));
  Network::addRequest(Request::Connexion, std::bind(&ServerMenu::abortConnexion, this, _1));

  // Aborting
  _msg->setDescription(new String("Aborting connection..."));
  _msg->getButton(0)->setState(Drawable::Pressed);

  _state = Aborting;

  return (false);
}
