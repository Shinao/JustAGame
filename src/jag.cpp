#include "jag.hh"
#include "Utility/Graphic.hh"

namespace jag
{
  void			init()
  {
    Theme		*theme = new Theme;
    _themes["titlebar"] = theme;

    // Setting the titlebar theme
    theme->c_background = sf::Color::White;
    theme->c_background_focused = sf::Color::White;
    theme->size_border = 0;

    theme = new Theme;
    _themes["menu"] = theme;
    // Setting the menu theme
    theme->c_text = sf::Color::Black;
    theme->c_text_focused = sf::Color::Black;
    theme->c_text_pressed = sf::Color::Black;
    theme->size_text = 12;
    theme->size_text_focused = 12;
    theme->size_text_pressed = 12;
    theme->c_background = sf::Color::White;
    theme->c_background_focused = sf::Color::White;
    theme->c_background_pressed = sf::Color::White;
    theme->style_text = sf::Text::Regular;
    theme->style_text_focused = sf::Text::Regular;
    theme->style_text_pressed = sf::Text::Regular;
    theme->f_text.loadFromFile("rsrc/arial.ttf");
    theme->f_text_focused = theme->f_text;
    theme->f_text_pressed = theme->f_text;
    theme->c_border = sf::Color::Black;
    theme->c_border_focused = sf::Color::Blue;
    theme->c_border_pressed = sf::Color::Blue;
    theme->size_border = 2;

    _theme = theme;

    // Init ressources
    sf::Image		&img = getRessource("close_window.png");
    sf::Image		&img1 = getRessource("minimize_window.png");
    sf::Image		&img2 = getRessource("restore_window.png");
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
