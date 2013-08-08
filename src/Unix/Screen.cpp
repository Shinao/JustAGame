#include "GUI/Screen.hh"

namespace Screen
{
  namespace
  {
    XID					cursor;
    Display				*display = XOpenDisplay(NULL);
  }

  void					minimize()
  {
    XIconifyWindow(display, Screen::getWindow().getSystemHandle(), DefaultScreen(display));
    XFlush(display);
    mouseLeft();
  }

  void					setCursor(Cursor::Type type)
  {
    switch(type)
    {
      case Cursor::Wait:
	cursor = XCreateFontCursor(display, XC_watch);
	break;
      case Cursor::Hand:
	cursor = XCreateFontCursor(display, XC_hand1);
	break;
      case Cursor::Normal:
	cursor = XCreateFontCursor(display, XC_left_ptr);
	break;
      case Cursor::Text:
	cursor = XCreateFontCursor(display, XC_xterm);
	break;
	// For more cursor options on Linux go here:
	// http://www.tronche.com/gui/x/xlib/appendix/b/
    }

    XDefineCursor(display, Screen::getHandle(), cursor);
    XFlush(display);
  }
}
