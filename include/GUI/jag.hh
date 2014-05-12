#ifndef JAG_HH_
# define JAG_HH_

# include "Theme.hh"
# include "SimpleIni.hpp"

// Everything needed for the client application
// Window properties - themes - fonts - etc

// Because fuck static class
// Init at first - clear at the end

# define INI_FILE	"rsrc/client.ini"
# define INI_GROUP	"client"

typedef sf::Rect<int> Rect;

namespace jag
{
  struct			Keys
  {
    std::string			label;
    sf::Keyboard::Key		key;
  };

  const std::string		WindowName = "JustAGame";
  const std::string		RessourcePath = "rsrc/";
  const int			WindowHeight = 576;
  const int			WindowWidth = 1024;
  const int			FPSTime = 1000 / 60;
  const int			MarginFPS = 4;
  const int			WindowBorderSize = 1;
  const int			MarginMenu = 84;


  void				init();
  void				clear();
  CSimpleIniA			&getSettings();
  Theme				*getCurrentTheme();
  Theme				*getTheme(const std::string &theme);
  void				setTheme(Theme *theme);
  void				addTheme(const std::string &name, Theme *theme);
  sf::Image			&getRessource(const std::string &name);
  void				createRessourceFromArray(const std::string &name,
      const unsigned char *data, unsigned int width, unsigned int height);
  std::map<std::string, sf::Keyboard::Key>		&getKeys();
  const std::string					&getValueFromEvent(sf::Keyboard::Key key);
  const std::string					&getValueFromEvent(sf::Mouse::Button btn);
}

#endif
