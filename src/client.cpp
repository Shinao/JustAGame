#include <SFML/System.hpp>
#include "Screen/Screen.hh"
#include "Setting.hh"

int		main(int ac, char **av)
{
  bool		updated = true;
  sf::Clock	timer;
  sf::Time	sleeping_time = sf::milliseconds(Setting::FPS - Setting::MARGIN_FPS);

  Screen::init();

  while (Screen::hasLayer())
  {
    if (timer.getElapsedTime().asMilliseconds() > Setting::FPS)
    {
      Screen::update();
      timer.restart();
      updated = true;
    }

    // Sleep if just updated
    if (updated)
    {
      // Sleep FPS minus MARGIN_FPS ms - keep FPS stable if lot of updates
      sf::sleep(sleeping_time);
      updated = false;
    }
  }

  return (EXIT_SUCCESS);
}
