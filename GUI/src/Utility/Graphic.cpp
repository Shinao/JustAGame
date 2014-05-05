#include "Utility/Graphic.hh"
#include <sstream>
#include <iostream>

namespace Utility
{
  void			changeColor(sf::Image &img, sf::Color c_old, sf::Color c_new)
  {
    sf::Vector2u	size = img.getSize();
    unsigned		x = 0, y = 0;

    while (y < size.y)
    {
      // Check color
      if (img.getPixel(x, y) == c_old)
	img.setPixel(x, y, c_new);

      // End of pixel line
      if (++x == size.x)
      {
	x = 0;
	++y;
      }
    }
  }

  void			initBorderByType(sf::RectangleShape &border, const Rect &rec, unsigned size_border, Border::Type type)
  {
    if (type != Border::None)
      switch (type)
      {
	case Border::Top:
	  border.setPosition(rec.left, rec.top - size_border);
	  border.setSize(sf::Vector2f(rec.width, size_border));
	  break;

	case Border::Bottom:
	  border.setPosition(rec.left, rec.top + rec.height);
	  border.setSize(sf::Vector2f(rec.width, size_border));
	  break;

	case Border::Left:
	  border.setPosition(rec.left - size_border, rec.top);
	  border.setSize(sf::Vector2f(size_border, rec.height));
	  break;

	default:
	  border.setPosition(rec.left + rec.width, rec.top);
	  border.setSize(sf::Vector2f(size_border, rec.height));
      }
  }

  sf::Color		stringToColor(const std::string &str)
  {
    sf::Color		color;
    std::stringstream	ss(str);
    unsigned int	nb;

    ss >> std::hex >> nb;
    
    color.r = nb / 0x10000;
    color.g = nb / 0x100 % 0x100;
    color.b = nb % 0x100;
    color.a = 255;

    return (color);
  }
}
