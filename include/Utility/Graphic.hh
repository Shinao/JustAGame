#ifndef GRAPHIC_HH_
# define GRAPHIC_HH_

# include <SFML/Graphics.hpp>
# include "jag.hh"
# include "GUI/Theme.hh"

namespace Utility
{
  void			changeColor(sf::Image &img, sf::Color c_old, sf::Color c_new);
  void			initBorderByType(sf::RectangleShape &border, const Rect &rec, unsigned size_border, Border::Type type);
}

#endif
