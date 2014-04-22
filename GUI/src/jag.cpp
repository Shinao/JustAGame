#include "jag.hh"
#include "Utility/Graphic.hh"
#include <iostream>

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
    // Predef color
    // sf::Color blue = sf::Color(78, 166, 234);
    sf::Color blue_focus = sf::Color(63, 146, 210);
    sf::Color blue_light = sf::Color(196, 216, 236);
    sf::Color gray = sf::Color(236, 236, 236);
    sf::Color gray_focus = sf::Color(216, 216, 216);
    sf::Color black_light = sf::Color(120, 120, 120);
    sf::Color black = sf::Color(100, 100, 100);

    // Setting the titlebar theme
    Theme		*theme = new Theme;
    _themes["Titlebar"] = theme;
    theme->c_background = sf::Color::Transparent;
    theme->c_background_focused = gray;
    theme->c_background_pressed = sf::Color::Transparent;
    theme->c_text = black_light;
    theme->c_text_focused = black_light;
    theme->c_text_pressed = black_light;

    // Setting the titlebar cross icon theme
    theme = new Theme;
    _themes["TitlebarCross"] = theme;
    *theme = *(_themes["Titlebar"]);
    theme->c_background_focused = sf::Color(236, 176, 176);
    theme->c_text_focused = sf::Color::White;

    theme = new Theme;
    _themes["White"] = theme;
    // Setting the menu theme
    theme->c_text = black;
    theme->c_text_focused = black;
    theme->c_text_pressed = sf::Color::White;
    theme->size_text = 12;
    theme->size_text_focused = 12;
    theme->size_text_pressed = 12;
    theme->c_background = sf::Color::White;
    theme->c_background_focused = gray;
    theme->c_background_pressed = black_light;
    theme->style_text = sf::Text::Regular;
    theme->style_text_focused = sf::Text::Regular;
    theme->style_text_pressed = sf::Text::Regular;
    theme->f_text.loadFromFile("rsrc/arial.ttf");
    theme->f_text_focused = theme->f_text;
    theme->f_text_pressed = theme->f_text;
    theme->c_border = gray;
    theme->c_border_focused = blue_light;
    theme->c_border_pressed = blue_focus;
    theme->size_border = 3;
    theme->size_border_focused = 3;
    theme->size_border_pressed = 3;

    _theme = theme;

    // Button theme
    theme = new Theme;
    _themes["Button"] = theme;
    *theme = *_themes["White"];
    theme->c_background = gray;
    theme->c_background_focused = theme->c_background_pressed;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_border = theme->c_border_focused;
    theme->c_border_focused = theme->c_border_pressed;

    theme = new Theme;
    _themes["ItemListBox"] = theme;
    *theme = *_themes["Button"];
    theme->c_background_focused = gray_focus;
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
    theme->c_border = gray_focus;
    theme->c_border_pressed = theme->c_border_focused;

    theme = new Theme;
    _themes["ModalMessageBox"] = theme;
    *theme = *_themes["White"];
    theme->c_text = theme->c_text_pressed;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_background = theme->c_background_pressed;
    theme->c_background_focused = theme->c_background_pressed;

    theme = new Theme;
    _themes["ModalMessageBoxTitle"] = theme;
    *theme = *_themes["ModalMessageBox"];
    theme->size_text = theme->size_text + 2;
    theme->size_text_focused = theme->size_text;
    theme->size_text_pressed = theme->size_text;
    theme->c_text = theme->c_text_pressed;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_background = black;
    theme->c_background_focused = black;
    theme->c_border = theme->c_border_pressed;
    theme->c_border_focused = theme->c_border_pressed;

    // Button theme
    theme = new Theme;
    _themes["ModalMessageBoxButton"] = theme;
    *theme = *_themes["Button"];
    theme->c_background = gray;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_border = theme->c_border_focused;
    theme->c_background_focused = theme->c_border;
    theme->c_border_focused = theme->c_background;

    // Transparent theme
    theme = new Theme;
    _themes["Transparent"] = theme;
    *theme = *_themes["White"];
    theme->c_background = sf::Color::Transparent;
    theme->c_background_focused = sf::Color::Transparent;
    theme->c_background_pressed = sf::Color::Transparent;
    theme->c_text_focused = theme->c_text;
    theme->c_text_pressed = theme->c_text;

    // Ping theme
    theme = new Theme;
    _themes["Ping"] = theme;
    *theme = *_themes["Transparent"];
    theme->c_border = blue_focus;
    theme->c_border_focused = blue_focus;
    theme->c_border_pressed = blue_focus;

    // ListItem
    theme = new Theme;
    _themes["ListItem"] = theme;
    *theme = *_themes["White"];

    theme = new Theme;
    _themes["ItemListItem"] = theme;
    *theme = *_themes["White"];

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
