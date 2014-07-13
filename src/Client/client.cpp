#include <SFML/System.hpp>
#include "Screen.hh"
#include "Network.hh"
#include "jag.hh"
#include "Layer.hh"
#include "ModalMessageBox.hh"
#include "Titlebar.hh"
#include "Background.hh"
#include "MainMenu.hh"
#include "StatusBar.hh"
#include "Action.hh"
#include "GameManager.hh"

#include "Test.hh"

// Once upon a main
// Arg : can take a port number for multiple client on same machine
int		main(int ac, char **av)
{
  sf::Clock	timer;
  sf::Time	sleeping_time = sf::milliseconds(jag::FPS_TIME - jag::MARGIN_FPS);
  int		port = (ac > 1 ? std::atoi(av[1]) : Network::CLIENT_PORT);

  // TODO - remove
  Screen::debug(Network::CLIENT_PORT == port ? 0 : 1);

  // Init ressources
  jag::init();
  Screen::init();

  new Background();
  new Titlebar();
  new MainMenu();
  new StatusBar();

  // Init network and check
  if (!Network::init(port, false))
    new ModalMessageBox("Network Error", new String("Game can not start. Port already used (25052/52025)."), false);

  // TODO - Remove
  // new Test();

  while (Screen::isActive())
  {
    Network::update();
    Screen::update();

    // Sleep FPS minus MARGIN_FPS ms - keep FPS stable if lots of updates
    sf::sleep(sleeping_time);
  }

  if (GameManager::isRunning())
    GameManager::exitGame();

  // Free ressources
  Network::clear();
  jag::clear();
  Screen::clear();

  return (EXIT_SUCCESS);
}
