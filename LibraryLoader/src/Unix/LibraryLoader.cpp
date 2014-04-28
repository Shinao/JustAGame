#include "LibraryLoader.hh"

LibraryLoader::LibraryLoader(const std::string &name) :
  m_libFunction(NULL),
  m_hndl(NULL)
{
  _lib_name = "lib" + name + ".so";
}

LibraryLoader::~LibraryLoader()
{
  if (m_hndl != NULL)
    dlclose(m_hndl);
}

// Load Library
bool		LibraryLoader::open()
{
  m_hndl = dlopen(_lib_name.c_str(), RTLD_LAZY | RTLD_NODELETE);

  if(m_hndl == NULL)
    return (false);

  return (true);
}

void		*LibraryLoader::getFunction(const std::string &name)
{
  m_libFunction = dlsym(m_hndl, name.c_str());

  if (m_libFunction == NULL)
    return (NULL);

  return (m_libFunction);
}
