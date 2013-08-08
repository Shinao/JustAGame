#include <windows.h>
#include "GUI/Screen.hh"

namespace Screen
{
  namespace
  {
    HCURSOR				cursor;
  }

  void					minimize()
  {
    ShowWindow((HWND__ *) Screen::getWindow().getSystemHandle(), SW_MINIMIZE);
    mouseLeft();
  }

  void					setCursor(Cursor::Type type)
  {
    switch(type)
    {
      case Cursor::Wait :
	cursor = LoadCursor(NULL, IDC_WAIT);
	break;
      case Cursor::Hand :
	cursor = LoadCursor(NULL, IDC_HAND);
	break;
      case Cursor::Normal :
	cursor = LoadCursor(NULL, IDC_ARROW);
	break;
      case Cursor::Text :
	cursor = LoadCursor(NULL, IDC_IBEAM);
	break;
	//For more cursor options on Windows go here:
	// http://msdn.microsoft.com/en-us/library/ms648391%28v=vs.85%29.aspx
    }

    SetClassLongPtr(Screen::getHandle(), GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(cursor));
  }
}
