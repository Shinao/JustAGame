#include "LibraryLoader.hh"
#include <direct.h>

LibraryLoader::LibraryLoader(const std::string &name, const std::string &path) :
  m_libFunction(NULL)
{
  _lib_name = path + "lib" + name + ".dll";
}

LibraryLoader::~LibraryLoader()
{
  if (m_hinstlib != NULL)
    FreeLibrary(m_hinstlib);
}

// Load Library
bool		LibraryLoader::open()
{
  m_hinstlib = LoadLibrary(TEXT(_lib_name.c_str()));

  if (m_hinstlib == NULL)
    return (false);

  return (true);
}

// Get function pointer
void		*LibraryLoader::getFunction(const std::string &name)
{
  m_libFunction = (void *) GetProcAddress(m_hinstlib, name.c_str());

  if (m_libFunction == NULL)
    return (NULL);

  return (m_libFunction);
}

const std::string	&LibraryLoader::getFullPath() const
{
  return (_lib_name);
}

LibraryLoader::System	LibraryLoader::getSystem()
{
  return (Win32);
}

bool			LibraryLoader::createDirectory(const std::string &name)
{
  return ((_mkdir(name.c_str()) == 0) ? true : false);
}
