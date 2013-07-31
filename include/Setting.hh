#ifndef SETTING_HH_
# define SETTING_HH_

# include "Screen/Theme.hh"

// Everything needed for the client application
// Window properties - themes - fonts - etc

namespace Setting
{
  // Can't catch me mothafucka
  namespace
  {
    Theme			_theme;
  }

  const int		windowHeight = 400;
  const int		windowWidth = 800;
  const int		FPS = 1000 / 60;
  const int		MARGIN_FPS = 4;

  void			init();
  void			clear();
  Theme			&getTheme();
}

#endif
