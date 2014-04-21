#ifndef PHYSIC_HH_
# define PHYSIC_HH_

# include <SFML/Graphics.hpp>

// A complete physic environment in one function

namespace Physic
{
  bool			isPointIn(int px, int py, int x, int y, int width, int height);
}

#endif
