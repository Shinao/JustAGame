#ifndef THEME_HH_
# define THEME_HH_

# include <SFML/Graphics.hpp>

// Theme for the menus - properties and stuffs

enum CursorType { Wait, Text, Normal, Hand };

namespace Border
{
  enum Type
  {
    None,
    Left,
    Right,
    Top,
    Bottom
  };
}

namespace Alignment
{
  enum Type
  {
    Left,
    Right,
    Center
  };
}

struct Theme
{
  sf::Color			c_text;
  sf::Color			c_text_focused;
  sf::Color			c_text_pressed;
  unsigned			size_text;
  unsigned			size_text_focused;
  unsigned			size_text_pressed;
  sf::Color			c_background;
  sf::Color			c_background_focused;
  sf::Color			c_background_pressed;
  sf::Text::Style		style_text;
  sf::Text::Style		style_text_focused;
  sf::Text::Style		style_text_pressed;
  sf::Font			f_text;
  sf::Font			f_text_focused;
  sf::Font			f_text_pressed;
  sf::Color			c_border;
  sf::Color			c_border_focused;
  sf::Color			c_border_pressed;
  unsigned			size_border;
  unsigned			size_border_focused;
  unsigned			size_border_pressed;
  sf::Color			c_mask_focused;
  Border::Type			border = Border::None;
  Alignment::Type		alignment = Alignment::Left;
};

#endif
