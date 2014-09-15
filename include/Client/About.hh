#ifndef ABOUT_HH_
# define ABOUT_HH_

# include "GUI/Layer.hh"
# include "Client/MainMenuItem.hh"
# include "GUI/String.hh"
# include "GUI/StringArea.hh"

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
