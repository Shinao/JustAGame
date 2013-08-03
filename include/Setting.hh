#ifndef SETTING_HH_
# define SETTING_HH_

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
    Theme				*_theme;
  }

  const int			windowHeight = 400;
  const int			windowWidth = 800;
  const int			FPS = 1000 / 60;
  const int			MARGIN_FPS = 4;

  void				init();
  void				clear();
  Theme				*getCurrentTheme();
  Theme				*getTheme(const std::string &theme);
  void				setTheme(Theme *theme);
  void				addTheme(const std::string &name, Theme *theme);
}

#endif
