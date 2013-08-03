#ifndef SPRITE_HH_
# define SPRITE_HH_

# include "GUI/Item.hh"

class Sprite : public Item
{
  private:
    Sprite(int id, Theme *theme = NULL, Alignment align = Left, float scale = 1.0f);
    sf::Sprite			*_sprite;

  public:
    Sprite() = delete;
    ~Sprite();

    void			setSprite(sf::Sprite *text);
    sf::Sprite			*getSprite();
    void			setRect(const Rect &rec);

    void			draw(sf::RenderWindow &win);
    void			update();
};

#endif
