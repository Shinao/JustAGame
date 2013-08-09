#include <windows.h>
#include "GUI/Screen.hh"

namespace
{
  HCURSOR				cursor;
}

void					Screen::minimize()
{
  ShowWindow((HWND__ *) Screen::getWindow().getSystemHandle(), SW_MINIMIZE);
}

void					Screen::setCursor(CursorType type)
{
  switch(type)
  {
    case Wait :
      cursor = LoadCursor(NULL, IDC_WAIT);
      break;
    case Hand :
      cursor = LoadCursor(NULL, IDC_HAND);
      break;
    case Normal :
      cursor = LoadCursor(NULL, IDC_ARROW);
      break;
    case Text :
      cursor = LoadCursor(NULL, IDC_IBEAM);
      break;
      //For more cursor options on Windows go here:
      // http://msdn.microsoft.com/en-us/library/ms648391%28v=vs.85%29.aspx
  }

  SetClassLongPtr(Screen::getHandle(), GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(cursor));
}
