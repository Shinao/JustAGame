#ifndef TITLEBAR_HH_
# define TITLEBAR_HH_

# include "GUI/Layer.hh"
# include "GUI/HorizontalMenu.hh"
# include "GUI/Sprite.hh"

class Titlebar : public Layer
{
  private:
    const int			MENU_WIDTH = 28;

    const int			TITLEBAR_HEIGHT = 36;
    HorizontalMenu		*_menu;
    sf::Sprite			_cross_spr;
    sf::Texture			_cross_tex;
    sf::Sprite			_min_spr;
    sf::Texture			_min_tex;
    sf::Sprite			_res_spr;
    sf::Texture			_res_tex;
    sf::Sprite			_icon_spr;
    sf::Texture			_icon_tex;
    sf::Sprite			_logo_spr;
    sf::Texture			_logo_tex;

  public:
    Titlebar();
    ~Titlebar();
    void			clicked(int x, int y);
    void			minimizeWindow();
    void			restoreWindow();
    void			draw(sf::RenderWindow &window);
    bool			update(sf::RenderWindow &window);
    bool			catchMouse();
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
