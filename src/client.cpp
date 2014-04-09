#include <SFML/System.hpp>
#include "GUI/Screen.hh"
#include "Network/Network.hh"
#include "jag.hh"
#include "GUI/Layer.hh"
#include "GUI/ModalMessageBox.hh"
#include "Titlebar.hh"
#include "Background.hh"
#include "MainMenu.hh"
#include "StatusBar.hh"
#include "GUI/Action.hh"

#include "Test.hh"

// Once upon a main
int		main()
{
  sf::Clock	timer;
  sf::Time	sleeping_time = sf::milliseconds(jag::FPSTime - jag::MarginFPS);

  // Init ressources
  Screen::init(Screen::Setting);
  jag::init();

  new Background();
  new Titlebar();
  new MainMenu();
  new StatusBar();

  // Init network and check
  if (!Network::init(52025, false))
    ModalMessageBox *msg = new ModalMessageBox("Network Error", new String("Game can not start. Port already used (25052/52025)."));

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
