#include "LibraryLoader.hh"

LibraryLoader::LibraryLoader(const std::string &name) :
  m_libFunction(NULL)
{
  _lib_name = "lib" + name + ".dll";
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
