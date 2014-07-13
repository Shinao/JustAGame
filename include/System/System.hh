#ifndef SYSTEM_HH_
# define SYSTEM_HH_

# include <string>

namespace System
{
  enum Type
  {
    Win32,
    Unix
  };

  Type			getType();
  bool			createDirectory(const std::string &name);
}

#endif
