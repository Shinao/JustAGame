#ifndef LIBRARYLOADER_HH_
# define LIBRARYLOADER_HH_

#include <windows.h>
#include <stdio.h>
#include <string>
#include <stdexcept>
#include <winsock2.h>
#include <ws2tcpip.h>

class LibraryLoader
{
  private:
    void 		*m_libFunction; 
    HINSTANCE		m_hinstlib;
    std::string		_lib_name;

  public:
    LibraryLoader(const std::string &name, const std::string &path = "./");
    ~LibraryLoader();

    bool		open();
    void		*getFunction(const std::string &name);
    const std::string	&getFullPath() const;
};

#endif
