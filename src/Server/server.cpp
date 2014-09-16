#include <string>
#include "Network/Network.hh"
#include "System/LibraryLoader.hh"
#include "SimpleIni/SimpleIni.hpp"
#include "server/AGameServer.hh"

int		error(const std::string &str)
{
  std::cerr << str << std::endl;
  return (EXIT_FAILURE);
}

// Once upon a main
int		main()
{
  sf::Clock	timer;
  sf::Time	sleeping_time = sf::milliseconds(100);
  bool		running = true;

  // Init network and check
  if (!Network::init(Network::SERVER_PORT, true))
    return (error("Game can not start. Port already used (25052/52025)."));

  // Check setting file
  CSimpleIniA	ini;
  ini.SetUnicode();
  if (ini.LoadFile(INI_FILE) < 0)
    return (error("Setting file server.ini missing"));

  std::string	game_mode = ini.GetValue(INI_GROUP, "game_mode", "");
  if (game_mode.empty())
    return (error("Game name does not exist"));

  std::string	lib_name = game_mode + Network::SUFFIX_SERVER;

  // Get Library from game name and load it
  LibraryLoader	lib(lib_name, Network::getPath(Network::BuildDir, game_mode));
  if (!lib.open())
    return (error("Could not open library : " + lib.getFullPath()));

  // Get the game
  typedef AGameServer *(*f_getGame)();
  f_getGame	func_ptr = (f_getGame) lib.getFunction("getGame");
  if (func_ptr == NULL)
    return (error("Library is corrupted, missing function getGame() - see extern \"C\""));
  AGameServer	*game = func_ptr();

  if (!game->init(ini))
    return (error("Init of GameServer failed : check " INI_FILE));
  game->run();

  // Everything's okay - Go go go !
  while (running)
  {
    Network::update();

    game->update();

    // Sleep
    sf::sleep(sleeping_time);
  }

  // Free ressources
  delete game;
  Network::clear();

  return (EXIT_SUCCESS);
}

