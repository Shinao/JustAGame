#ifndef MAIN_MENU_ITEM_HH_
# define MAIN_MENU_ITEM_HH_

# include "Layer.hh"
# include "Menu.hh"
# include "String.hh"

class MainMenuItem : public Layer
{
  public:
    static const int		WIDTH = 650;
    static const int		HEIGHT = 32;
    static const int		PADDING = 128;
    static const int		MARGIN = 32;

  protected:
    Menu			*_menu;
    int				_y_content;
    String			*_title;

  public:
    MainMenuItem(const std::string &name);
    ~MainMenuItem();

    void			draw(sf::RenderWindow &);
};

#endif


