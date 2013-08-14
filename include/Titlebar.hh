#ifndef TITLEBAR_HH_
# define TITLEBAR_HH_

# include "GUI/Layer.hh"
# include "GUI/Menu.hh"

class Titlebar : public Layer
{
  public:
    static const int		MENU_HEIGHT = 28;
    static const int		MENU_MARGIN = 8;
    static const int		HEIGHT = 36;

  private:
    Menu			*_menu;
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
    Titlebar(Screen &screen);
    ~Titlebar();
    void			pressed(int x, int y);
    void			released(int x, int y);
    void			minimize();
    void			restore();
    void			draw(sf::RenderWindow &window);
    bool			update(sf::RenderWindow &window);
    bool			catchMouse();
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
