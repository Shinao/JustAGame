#include "System/System.hh"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

namespace System
{
  OS			getOS()
  {
    return (Unix);
  }

  bool			createDirectory(const std::string &name)
  {
    return ((mkdir(name.c_str(), 641) == 0) ? true : false);
  }

  std::vector<File *>	*getFiles(const std::string &name)
  {
    DIR			*dir;
    struct dirent 	*ent;
    struct stat 	st;
    std::vector<File *>	*list = new std::vector<File *>();
    File		*file;

    dir = opendir(name.c_str());
    while ((ent = readdir(dir)) != NULL)
    {
      std::string	file_name = ent->d_name;
      std::string	full_file_name = name + "/" + file_name;

      if (stat(full_file_name.c_str(), &st) == -1)
	continue;

      file = new File;
      file->name = file_name;
      file->size = st.st_size;
      file->type = ((st.st_mode & S_IFDIR) != 0 ? File::FolderType : File::FileType);

      list->push_back(file);
    }

    closedir(dir);
    return (list);
  }
}
