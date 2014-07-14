#include "System.hh"
#include <cstdio>

namespace System
{
  bool				removeFile(const std::string &name)
  {
    return (remove(name.c_str()) == 0);
  }
}
