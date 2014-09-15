#include "System/System.hh"
#include <direct.h>
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <iostream>
// #pragma comment(lib, "User32.lib")

namespace System
{
  OS			getOS()
  {
    return (Win32);
  }

  bool			createDirectory(const std::string &name)
  {
    return ((_mkdir(name.c_str()) == 0) ? true : false);
  }

  std::vector<File *>	*getFiles(const std::string &name)
  {
    std::string		name_fix;
    WIN32_FIND_DATA	ffd;
    LARGE_INTEGER	filesize;
    HANDLE 		hFind = INVALID_HANDLE_VALUE;
    File		*file;
    std::vector<File *>	*list = new std::vector<File *>();

    if (name.length() > (MAX_PATH - 3))
      return (NULL);

    name_fix = name + "\\*";
    hFind = FindFirstFile(name_fix.c_str(), &ffd);

    if (INVALID_HANDLE_VALUE == hFind) 
      return (NULL);

    do
    {
      file = new File;
      file->name = ffd.cFileName;
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
	file->size = 0;
	file->type = File::FolderType;
	std::cout << "FOLDER: " << ffd.cFileName << std::endl;
      }
      else
      {
	filesize.LowPart = ffd.nFileSizeLow;
	filesize.HighPart = ffd.nFileSizeHigh;
	file->size = filesize.QuadPart;
	file->type = File::FileType;
	std::cout << "FILE: " << ffd.cFileName << " [" << filesize.QuadPart << " bytes]" << std::endl;
      }

      list->push_back(file);
    }
    while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);

    return (list);
  }
}
