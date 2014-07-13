#include "System.hh"
#include <direct.h>

namespace System
{
  Type			getType()
  {
    return (Win32);
  }

  bool			createDirectory(const std::string &name)
  {
    return ((_mkdir(name.c_str()) == 0) ? true : false);
  }
}
