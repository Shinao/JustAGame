#include "System.hh"

namespace System
{
  Type			getType()
  {
    return (Unix);
  }

  bool			createDirectory(const std::string &name)
  {
    return ((mkdir(name.c_str(), 641) == 0) ? true : false);
  }
}
