#include <SFML/System.hpp>
#include "GUI/Screen.hh"
#include "Setting.hh"
#include "GUI/Layer.hh"
#include "Titlebar.hh"

// Once upon a main
int		main(int ac, char **av)
{
  bool		updated = false;
  sf::Clock	timer;
  sf::Time	sleeping_time = sf::milliseconds(Setting::FPS - Setting::MARGIN_FPS);

  Setting::init();
  Screen::init();
  Screen::add(new Titlebar);

  while (Screen::hasLayer())
  {
    Screen::update();

    // Sleep FPS minus MARGIN_FPS ms - keep FPS stable if lots of updates
    sf::sleep(sleeping_time);
  }

  Screen::clear();
  Setting::clear();

  return (EXIT_SUCCESS);
}
