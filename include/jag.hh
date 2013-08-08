#ifndef JAG_HH_
# define JAG_HH_

# include <SFML/Graphics.hpp>
# include "GUI/Theme.hh"

# include <iostream>

// Everything needed for the client application
// Window properties - themes - fonts - etc

typedef sf::Rect<int> Rect;

namespace jag
{
  const std::string		WindowName = "JustAGame";
  const std::string		RessourcePath = "rsrc/";
  const int			WindowHeight = 576;
  const int			WindowWidth = 1024;
  const int			FPS = 1000 / 60;
  const int			MarginFPS = 4;

  void				init();
  void				clear();
  Theme				*getCurrentTheme();
  Theme				*getTheme(const std::string &theme);
  void				setTheme(Theme *theme);
  void				addTheme(const std::string &name, Theme *theme);
  sf::Image			&getRessource(const std::string &name);
}

#endif
