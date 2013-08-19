#include <string>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>

enum CursorType { Wait, Text, Normal, Hand };

namespace
{
  XID				cursor;
  Display			*display = XOpenDisplay(NULL);
}

void				minimizeImpl(Window handle)
{
  XIconifyWindow(display, handle, DefaultScreen(display));
  XFlush(display);
}

void				setCursorImpl(Window handle, CursorType type)
{
  switch (type)
  {
    case Wait:
      cursor = XCreateFontCursor(display, XC_watch);
      break;
    case Hand:
      cursor = XCreateFontCursor(display, XC_hand1);
      break;
    case Normal:
      cursor = XCreateFontCursor(display, XC_left_ptr);
      break;
    case Text:
      cursor = XCreateFontCursor(display, XC_xterm);
      break;
      // For more cursor options on Linux go here:
      // http://www.tronche.com/gui/x/xlib/appendix/b/
  }

  XDefineCursor(display, handle, cursor);
  XFlush(display);
}

void			openUrlImpl(const std::string &url)
{
  system(std::string("xdg-open " + url).c_str());
}
