#ifndef MULTIMEDIA_HH_
# define MULTIMEDIA_HH_

# include "GUI/Layer.hh"
# include "Client/MainMenuItem.hh"
# include "GUI/Table.hh"

class Multimedia : public MainMenuItem
{
  private:
    bool			_video_mode;
    DrawableManager		_dmanager_backup;
    Table			*_table_video;

    void			toggleMode(bool video_mode);
    Drawable			*getDrawable(const std::string &name);
    void			applyChanges();

  public:
    Multimedia();
    ~Multimedia();

    void			settingChanged();
};

#endif
