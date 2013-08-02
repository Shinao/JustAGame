#ifndef STANDARDCURSOR_HPP
#define STANDARDCURSOR_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifdef SFML_SYSTEM_WINDOWS
#include <windows.h>
#elif defined(SFML_SYSTEM_LINUX)
#include <X11/cursorfont.h>
#include <X11/Xlib.h>
#else
#endif

namespace sf
{
  namespace
  {
#ifdef SFML_SYSTEM_WINDOWS

    HCURSOR cursor; /*Type of the Cursor with Windows*/

#elif defined(SFML_SYSTEM_LINUX)

    XID cursor;
    Display* display;

#endif
  }

  namespace Cursor
  {
    enum Type { Wait, Text, Normal, Hand };
  }

  void setCursor(Cursor::Type t);
}

#endif // STANDARDCURSOR_HPP
