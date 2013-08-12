#ifndef JAG_HH_
# define JAG_HH_

# include "GUI/Theme.hh"

// Everything needed for the client application
// Window properties - themes - fonts - etc

// Because fuck static class
// Init at first - clear at the end

typedef sf::Rect<int> Rect;

namespace jag
{
  const int			GRAY = 246;
  const std::string		WindowName = "JustAGame";
  const std::string		RessourcePath = "rsrc/";
  const int			WindowHeight = 576;
  const int			WindowWidth = 1024;
  const int			FPS = 1000 / 60;
  const int			MarginFPS = 4;
  const int			WindowBorderSize = 1;

  void				init();
  void				clear();
  Theme				*getCurrentTheme();
  Theme				*getTheme(const std::string &theme);
  void				setTheme(Theme *theme);
  void				addTheme(const std::string &name, Theme *theme);
  sf::Image			&getRessource(const std::string &name);
}

#endif
