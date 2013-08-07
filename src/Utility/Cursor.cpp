#include "Utility/Cursor.hh"
#include "GUI/Screen.hh"

#ifdef SFML_SYSTEM_WINDOWS

void sf::setCursor(sf::Cursor::Type t)
{
  switch(t)
  {
    case sf::Cursor::Wait :
      cursor = LoadCursor(NULL, IDC_WAIT);
      break;
    case sf::Cursor::Hand :
      cursor = LoadCursor(NULL, IDC_HAND);
      break;
    case sf::Cursor::Normal :
      cursor = LoadCursor(NULL, IDC_ARROW);
      break;
    case sf::Cursor::Text :
      cursor = LoadCursor(NULL, IDC_IBEAM);
      break;
      //For more cursor options on Windows go here:
      // http://msdn.microsoft.com/en-us/library/ms648391%28v=vs.85%29.aspx
  }

  SetClassLongPtr(Screen::getHandle(), GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(cursor));
}

#elif defined(SFML_SYSTEM_LINUX)

void sf::setCursor(sf::Cursor::Type t)
{
  display = XOpenDisplay(NULL);

  switch(t)
  {
    case sf::Cursor::Wait:
      cursor = XCreateFontCursor(display, XC_watch);
      break;
    case sf::Cursor::Hand:
      cursor = XCreateFontCursor(display, XC_hand1);
      break;
    case sf::Cursor::Normal:
      cursor = XCreateFontCursor(display, XC_left_ptr);
      break;
    case sf::Cursor::Text:
      cursor = XCreateFontCursor(display, XC_xterm);
      break;
      // For more cursor options on Linux go here:
      // http://www.tronche.com/gui/x/xlib/appendix/b/
  }

  XDefineCursor(display, Screen::getHandle(), cursor);
  XFlush(display);

  delete display;
}

#else

void sf::StandardCursor::set(const sf::StCursor::Type t) {}

#endif
