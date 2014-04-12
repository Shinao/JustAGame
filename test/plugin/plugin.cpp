#include "plugin.hh"
#include "network.hh"

extern "C"
{
  void	useDll()
  {
    Network::howManyTimes();
  }
}
