#include "GUI/Screen.hh"

namespace Screen
{
  void					minimize()
  {
    Display	*display = XOpenDisplay(NULL);

    XIconifyWindow(display, Screen::getWindow().getSystemHandle(), DefaultScreen(display));
    XFlush(display);
    delete display;
    mouseLeft();
  }
}
