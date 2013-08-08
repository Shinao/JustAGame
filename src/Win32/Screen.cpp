#include <windows.h>
#include "GUI/Screen.hh"

namespace Screen
{
  void					minimize()
  {
    ShowWindow((HWND__ *) Screen::getWindow().getSystemHandle(), SW_MINIMIZE);
    mouseLeft();
  }
}
