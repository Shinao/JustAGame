#ifndef ABOUT_HH_
# define ABOUT_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"
# include "String.hh"
# include "StringArea.hh"

class About : public MainMenuItem
{
  private:
    StringArea			*_area;
    String			*_visit;

  public:
    About();
    ~About();

    void			settingChanged();
};

#endif
