#ifndef GAMELAYER_HH_
# define GAMELAYER_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"

class GameLayer : public MainMenuItem
{
  private:
    const int			NB_COLOR = 4;
    const int			WIDTH_COLOR = 36;

    sf::VertexArray		_square_color_picker;
    sf::VertexArray		_tri_color_picker;
    sf::Color			_player_color;
    sf::Texture			*_tex_bird;
    sf::Sprite			*_spr_bird;

    void			setColorPickers(int x, int y);
    void			checkColorPickers(int x, int y);
    void			applyChanges();

  public:
    GameLayer();
    ~GameLayer();

    void			mousePressed(int x, int y);
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			settingChanged();
};

#endif
