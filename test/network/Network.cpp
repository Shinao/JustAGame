#include "Network.hh"

namespace Network
{
  namespace
  {
    int times = 0;
  }

  void		howManyTimes()
  {
    std::cout << times++ << std::endl;
  }
}
