#include "jag.hh"
#include "Utility/Graphic.hh"

namespace jag
{
  // Can't catch me mothafucka
  namespace
  {
    std::map<std::string, Theme	*>	_themes;
    std::map<std::string, sf::Image *>	_rsrcs;
    Theme				*_theme;
  }

  void			init()
  {
    Theme		*theme = new Theme;
    _themes["titlebar"] = theme;

    // Setting the titlebar theme
    theme->c_background = sf::Color::Transparent;
    theme->c_background_focused = sf::Color(GRAY, GRAY, GRAY);
    theme->c_background_pressed = sf::Color::Transparent;
    theme->size_border = 0;

    theme = new Theme;
    _themes["titlebar_cross"] = theme;
    *theme = *(_themes["titlebar"]);
    // Setting the titlebar cross icon theme
    theme->c_background_focused = sf::Color(255, 200, 200, 224);

    theme = new Theme;
    _themes["white"] = theme;
    // Setting the menu theme
    theme->c_text = sf::Color(100, 100, 100);
    theme->c_text_focused = sf::Color(100, 100, 100);
    theme->c_text_pressed = sf::Color(50, 50, 50);
    theme->size_text = 12;
    theme->size_text_focused = 12;
    theme->size_text_pressed = 12;
    theme->c_background = sf::Color::White;
    theme->c_background_focused = sf::Color(GRAY, GRAY, GRAY);
    theme->c_background_pressed = sf::Color(GRAY - 8, GRAY - 8, GRAY - 8);
    theme->style_text = sf::Text::Regular;
    theme->style_text_focused = sf::Text::Regular;
    theme->style_text_pressed = sf::Text::Regular;
    theme->f_text.loadFromFile("rsrc/arial.ttf");
    theme->f_text_focused = theme->f_text;
    theme->f_text_pressed = theme->f_text;
    theme->c_border = sf::Color(GRAY, GRAY, GRAY);
    theme->c_border_focused = sf::Color(GRAY - 16, GRAY - 16, GRAY - 16);
    theme->c_border_pressed = sf::Color(186, 186, GRAY);
    theme->size_border = 2;
    theme->size_border_focused = 2;
    theme->size_border_pressed = 2;

    _theme = theme;

    theme = new Theme;
    _themes["black"] = theme;
    *theme = *_themes["white"];
    sf::Color toBlack(60, 60, 60);
    theme->c_background *= toBlack;
    theme->c_background_focused *= toBlack;
    theme->c_background_pressed *= toBlack;
    theme->c_border *=  toBlack;
    theme->c_border_focused *= toBlack;
    theme->c_border_pressed *= toBlack;
    theme->c_text = sf::Color(150, 150, 150);
    theme->c_text_focused = sf::Color(150, 150, 150);
    theme->c_text_pressed = sf::Color(200, 200, 200);

    // Init ressources
    getRessource("close_window.png");
    getRessource("minimize_window.png");
    getRessource("restore_window.png");
  }

  void			clear()
  {
    // Clear themes
    for (auto it : _themes)
      delete it.second;

    // Clear ressources
    for (auto it : _rsrcs)
      delete it.second;
  }

  Theme			*getCurrentTheme()
  {
    return (_theme);
  }

  Theme			*getTheme(const std::string &name)
  {
    auto		it = _themes.find(name);

    if (it != _themes.end())
      return (it->second);

    return (_theme);
  }

  void			setTheme(Theme *theme)
  {
    _theme = theme;
  }

  void			addTheme(const std::string &name, Theme *theme)
  {
    _themes[name] = theme;
  }

  sf::Image		&getRessource(const std::string &name)
  {
    auto		it = _rsrcs.find(RessourcePath + name);

    if (it != _rsrcs.end())
      return (*(it->second));

    sf::Image		*img = new sf::Image;

    // No image found - fucking users deleting files !
    if (!img->loadFromFile(RessourcePath + name))
      img->create(16, 16);

    _rsrcs[RessourcePath + name] = img;
    return (*img);
  }
}
