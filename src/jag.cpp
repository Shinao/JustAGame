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
    _themes["Titlebar"] = theme;

    // Setting the titlebar theme
    theme->c_background = sf::Color::Transparent;
    theme->c_background_focused = sf::Color(GRAY, GRAY, GRAY);
    theme->c_background_pressed = sf::Color::Transparent;
    theme->size_border = 0;

    theme = new Theme;
    _themes["TitlebarCross"] = theme;
    *theme = *(_themes["Titlebar"]);
    // Setting the titlebar cross icon theme
    theme->c_background_focused = sf::Color(GRAY, GRAY - 60, GRAY - 60);

    theme = new Theme;
    _themes["White"] = theme;
    // Setting the menu theme
    theme->c_text = sf::Color(100, 100, 100);
    theme->c_text_focused = sf::Color(100, 100, 100);
    theme->c_text_pressed = sf::Color(255, 255, 255);
    theme->size_text = 12;
    theme->size_text_focused = 12;
    theme->size_text_pressed = 12;
    theme->c_background = sf::Color::White;
    theme->c_background_focused = sf::Color(GRAY, GRAY, GRAY);
    theme->c_background_pressed = sf::Color(100, 100, 100);
    theme->style_text = sf::Text::Regular;
    theme->style_text_focused = sf::Text::Regular;
    theme->style_text_pressed = sf::Text::Regular;
    theme->f_text.loadFromFile("rsrc/arial.ttf");
    theme->f_text_focused = theme->f_text;
    theme->f_text_pressed = theme->f_text;
    theme->c_border = sf::Color(GRAY, GRAY, GRAY);
    theme->c_border_focused = sf::Color(GRAY - 40, GRAY - 20, GRAY);
    theme->c_border_pressed = sf::Color(63, 146, 210);
    theme->size_border = 3;
    theme->size_border_focused = 3;
    theme->size_border_pressed = 3;

    _theme = theme;

    // Button theme
    theme = new Theme;
    _themes["Button"] = theme;
    *theme = *_themes["White"];
    theme->c_background = sf::Color(GRAY, GRAY, GRAY);
    theme->c_background_focused = theme->c_background_pressed;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_border = theme->c_border_focused;
    theme->c_border_focused = theme->c_border_pressed;

    theme = new Theme;
    _themes["ItemListBox"] = theme;
    *theme = *_themes["Button"];
    theme->c_background_focused = sf::Color(GRAY - 20, GRAY - 20, GRAY - 20);
    theme->c_text_focused = _themes["White"]->c_text_focused;

    theme = new Theme;
    _themes["Tooltip"] = theme;
    *theme = *_themes["White"];
    theme->c_background = theme->c_background_focused;
    theme->c_border = theme->c_border_focused;

    theme = new Theme;
    _themes["Input"] = theme;
    *theme = *_themes["White"];
    theme->c_background = theme->c_background_focused;
    theme->c_border = sf::Color(GRAY - 20, GRAY - 20, GRAY - 20);
    theme->c_border_pressed = theme->c_border_focused;

    theme = new Theme;
    _themes["MessageBox"] = theme;
    *theme = *_themes["White"];
    theme->c_text = theme->c_text_pressed;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_background = theme->c_background_pressed;
    theme->c_background_focused = theme->c_background_pressed;
    // theme->c_border_pressed = theme->c_border_focused;
    // theme->c_border_pressed = theme->c_border_focused;

    theme = new Theme;
    _themes["MessageBoxTitle"] = theme;
    *theme = *_themes["MessageBox"];
    theme->size_text = theme->size_text + 2;
    theme->size_text_focused = theme->size_text;
    theme->size_text_pressed = theme->size_text;
    theme->c_text = theme->c_text_pressed;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_background = theme->c_background_pressed;
    theme->c_background_focused = theme->c_background_pressed;
    theme->c_border = theme->c_border_pressed;
    theme->c_border_focused = theme->c_border_pressed;

    // Button theme
    theme = new Theme;
    _themes["MessageBoxButton"] = theme;
    *theme = *_themes["Button"];
    theme->c_background = sf::Color(GRAY, GRAY, GRAY);
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_border = theme->c_border_focused;
    theme->c_background_focused = theme->c_border;
    theme->c_border_focused = theme->c_background;


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
