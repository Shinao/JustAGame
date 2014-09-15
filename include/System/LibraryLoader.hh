#ifndef LIBRARYLOADER_HH_
# define LIBRARYLOADER_HH_

#ifdef __linux__
# include "System/Unix/LibraryLoaderImpl.hh"
#elif WIN32
# include "System/Win32/LibraryLoaderImpl.hh"
#endif

#endif
