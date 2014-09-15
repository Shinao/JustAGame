#include "GUI/Utility/Physic.hh"

namespace Physic
{
  bool		isPointIn(int px, int py, int x, int y, int width, int height)
  {
    sf::Rect<int> rec(x, y, width, height);
    return (rec.contains(px, py));
  }
}
