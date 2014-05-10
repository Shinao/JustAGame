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

#include "Test.hh"

// Once upon a main
// Arg : can take a port number for multiple client on same machine
int		main(int ac, char **av)
{
  sf::Clock	timer;
  sf::Time	sleeping_time = sf::milliseconds(jag::FPSTime - jag::MarginFPS);


  // Init ressources
  jag::init();
  Screen::init(Screen::Setting);

  new Background();
  new Titlebar();
  new MainMenu();
  new StatusBar();

  int	port = (ac > 1 ? std::atoi(av[1]) : Network::CLIENT_PORT);
  // Init network and check
  if (!Network::init(port, false))
    new ModalMessageBox("Network Error", new String("Game can not start. Port already used (25052/52025)."));

  // TODO - Remove
  // new Test();

  while (Screen::isActive())
  {
    Network::update();
    Screen::update();

    // Sleep FPS minus MARGIN_FPS ms - keep FPS stable if lots of updates
    sf::sleep(sleeping_time);
  }

  // Free ressources
  Network::clear();
  jag::clear();
  Screen::clear();

  return (EXIT_SUCCESS);
}
