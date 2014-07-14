#ifndef SYSTEM_HH_
# define SYSTEM_HH_

# include <string>
# include <vector>

namespace System
{
  enum OS
  {
    Win32,
    Unix,
  };
  
  struct File
  {
    std::string	name;
    unsigned	size;
    enum Type
    {
      FileType,
      FolderType
    }		type;
  };

  OS				getOS();
  bool				createDirectory(const std::string &name);
  std::vector<File *>		*getFiles(const std::string &name);
  bool				removeFile(const std::string &name);
}

#endif
