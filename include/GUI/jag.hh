#ifndef JAG_HH_
# define JAG_HH_

# include "Network/Network.hh"
# include "GUI/Theme.hh"
# include "SimpleIni/SimpleIni.hpp"

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

  const std::string		WINDOW_NAME = "JustAGame";
  const std::string		RESSOURCE_PATH = "rsrc/";
  const int			CLIENT_WIDTH = 1024;
  const int			CLIENT_HEIGHT = 576;
  const int			FPS_TIME = 1000 / 60;
  const int			MARGIN_FPS = 4;
  const int			WINDOW_BORDER_SIZE = 1;
  const int			MARGIN_MENU = 84;


  void				init();
  void				clear();
  CSimpleIniA			&getSettings();
  Theme				*getCurrentTheme();
  Theme				*getTheme(const std::string &theme);
  void				setTheme(Theme *theme);
  void				addTheme(const std::string &name, Theme *theme);
  sf::Image			&getRessource(const std::string &path);
  void				createRessourceFromArray(const std::string &path,
      const unsigned char *data, unsigned int width, unsigned int height);
  std::map<std::string, sf::Keyboard::Key>		&getKeys();
  const std::string					&getValueFromEvent(sf::Keyboard::Key key);
  const std::string					&getValueFromEvent(sf::Mouse::Button btn);
  sf::Keyboard::Key					getKeyFromValue(const std::string &value);
}

#endif
