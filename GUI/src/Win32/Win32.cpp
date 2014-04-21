#include <string>
#include <windows.h>
#include "Theme.hh"

namespace
{
  HCURSOR			cursor;
}

void				minimizeImpl(sf::WindowHandle handle)
{
  ShowWindow((HWND__ *) handle, SW_MINIMIZE);
}

void				setCursorImpl(sf::WindowHandle handle, CursorType type)
{
  switch (type)
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

  SetClassLongPtr(handle, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(cursor));
}

void			openUrlImpl(const std::string &url)
{
  system(std::string("start """ + url).c_str());
}
