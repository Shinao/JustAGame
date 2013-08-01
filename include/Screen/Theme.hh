#ifndef THEME_HH_
# define THEME_HH_

# include <SFML/Graphics.hpp>

// Theme for the menus - properties and stuffs

struct Theme
{
  sf::Color			c_text;
  sf::Color			c_text_focused;
  unsigned			size_text;
  unsigned			size_text_focused;
  sf::Color			c_background;
  sf::Color			c_background_focused;
  sf::Text::Style		style_text;
  sf::Text::Style		style_text_focused;
  sf::Font			f_text;

  // TODO
  // Complete Theme (line focus)
};

#endif
