#include <SFML/System.hpp>
#include "GUI/Screen.hh"
#include "jag.hh"
#include "GUI/Layer.hh"
#include "Titlebar.hh"
#include "Background.hh"
#include "MainMenu.hh"
#include "GUI/Action.hh"

// Once upon a main
int		main()
{
  Screen	screen(Screen::Setting);
  sf::Clock	timer;
  sf::Time	sleeping_time = sf::milliseconds(jag::FPS - jag::MarginFPS);

  jag::init();
  new Background(screen);
  new Titlebar(screen);
  new MainMenu(screen);

  while (Screen::isActive())
  {
    screen.update();

    // Sleep FPS minus MARGIN_FPS ms - keep FPS stable if lots of updates
    sf::sleep(sleeping_time);
  }

  jag::clear();

  return (EXIT_SUCCESS);
}

