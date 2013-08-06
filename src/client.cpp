#include <SFML/System.hpp>
#include "GUI/Screen.hh"
#include "jag.hh"
#include "GUI/Layer.hh"
#include "Titlebar.hh"

// Once upon a main
int		main(int ac, char **av)
{
  bool		updated = false;
  sf::Clock	timer;
  sf::Time	sleeping_time = sf::milliseconds(jag::FPS - jag::MarginFPS);

  jag::init();
  Screen::init();
  Screen::add(new Titlebar);

  while (Screen::isActive())
  {
    Screen::update();

    // Sleep FPS minus MARGIN_FPS ms - keep FPS stable if lots of updates
    sf::sleep(sleeping_time);
  }

  Screen::clear();
  jag::clear();

  return (EXIT_SUCCESS);
}
