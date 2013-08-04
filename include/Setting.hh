#ifndef SETTING_HH_
# define SETTING_HH_

# include <SFML/Graphics.hpp>
# include "GUI/Theme.hh"

// Everything needed for the client application
// Window properties - themes - fonts - etc

typedef sf::Rect<int> Rect;

namespace Setting
{
  // Can't catch me mothafucka
  namespace
  {
    std::map<std::string, Theme	*>	_themes;
    std::map<std::string, sf::Image *>	_rsrcs;
    Theme				*_theme;
  }

  const std::string		RessourcePath = "rsrc/";
  const int			windowHeight = 400;
  const int			windowWidth = 800;
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
