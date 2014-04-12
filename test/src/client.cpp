#include "Network.hh"
#include <windows.h>
#include "plugin.hh"

typedef void (*f_funci)();

int	main()
{
  Network::howManyTimes();
  Network::howManyTimes();

  HINSTANCE hGetProcIDDLL = LoadLibrary("libplugin.dll");

  if (!hGetProcIDDLL) {
    std::cout << "could not load the dynamic library" << std::endl;
    return EXIT_FAILURE;
  }

  f_funci funci = (f_funci)GetProcAddress(hGetProcIDDLL, "useDll");
  if (!funci) {
    std::cout << "could not locate the function" << std::endl;
    return EXIT_FAILURE;
  }

  funci();
  

  return (0);
}
