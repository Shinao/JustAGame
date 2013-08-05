#include "Utility/Graphic.hh"

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
}
