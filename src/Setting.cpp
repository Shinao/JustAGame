#include "Setting.hh"


namespace Setting
{
  void			init()
  {
    // Setting the theme
    _theme.c_text = sf::Color::Black;
    _theme.c_text_focused = sf::Color::Black;
    _theme.size_text = 12;
    _theme.size_text_focused = 12;
    _theme.c_background = sf::Color::White;
    _theme.c_background_focused = sf::Color::White;
    _theme.style_text = sf::Text::Regular;
    _theme.style_text_focused = sf::Text::Regular;
    _theme.f_text.loadFromFile("rsrc/arial.ttf");
  }

  void			clear()
  {
    // Useless function ? You are useless !
  }

  Theme			&getTheme()
  {
    return (_theme);
  }
}
