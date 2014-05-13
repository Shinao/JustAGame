#ifndef LIBRARYLOADER_HH_
# define LIBRARYLOADER_HH_

# include <windows.h>
# include <stdio.h>
# include <stdexcept>
# include <winsock2.h>
# include <ws2tcpip.h>
# include <string>

class LibraryLoader
{
  private:
    void 		*m_libFunction; 
    HINSTANCE		m_hinstlib;
    std::string		_lib_name;

  public:
    enum Plateform
    {
      Win32,
      Unix
    };

    LibraryLoader(const std::string &name, const std::string &path = "./");
    ~LibraryLoader();

    bool		open();
    void		*getFunction(const std::string &name);
    const std::string	&getFullPath() const;
    static Plateform	getPlateform();
};

#endif
