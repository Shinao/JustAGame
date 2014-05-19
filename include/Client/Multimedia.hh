#ifndef MULTIMEDIA_HH_
# define MULTIMEDIA_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"
# include "Table.hh"

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
};

#endif
