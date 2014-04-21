#ifndef SPRITE_HH_
# define SPRITE_HH_

# include "Item.hh"

class Sprite : public Item
{
  private:
    sf::Sprite			*_sprite;

  public:
    Sprite(sf::Sprite *sprite, Theme *theme = jag::getCurrentTheme(), Alignment align = Left, float scale = 1.0f);
    ~Sprite();

    void			setSprite(sf::Sprite *sprite);
    sf::Sprite			*getSprite();
    void			setRect(const Rect &rec);

    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getRectRessource() const;
};

#endif
