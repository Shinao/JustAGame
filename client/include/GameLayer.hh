#ifndef GAMELAYER_HH_
# define GAMELAYER_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"

class GameLayer : public MainMenuItem
{
  private:
    sf::VertexArray		_square_color_picker;
    sf::VertexArray		_tri_color_picker;
    sf::Color			_player_color;
    sf::Texture			*_tex_bird;
    sf::Sprite			*_spr_bird;

  public:
    GameLayer();
    ~GameLayer();

    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif

