#ifndef LIBRARYLOADER_HH_
# define LIBRARYLOADER_HH_

#include <string>
#include <stdexcept>
#include <dlfcn.h>

class LibraryLoader
{
  private:
    void 		*m_libFunction; 
    void		*m_hndl;

    std::string		_lib_name;

  public:
    LibraryLoader(const std::string &name);
    ~LibraryLoader();

    bool 		open();
    void		*getFunction(const std::string &name);
};

#endif
