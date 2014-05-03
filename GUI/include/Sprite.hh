#ifndef SPRITE_HH_
# define SPRITE_HH_

# include "Item.hh"

// Sprite
// Sprite will change color depending on the color text of the theme

class Sprite : public Item
{
  private:
    sf::Sprite			*_sprite;

  public:
    Sprite(sf::Sprite *sprite, Theme *theme = jag::getCurrentTheme(), float scale = 1.0f);
    ~Sprite();

    void			setSprite(sf::Sprite *sprite);
    sf::Sprite			*getSprite();
    void			setRect(const Rect &rec);
    void			applyColor(const sf::Color &color);

    void			designChanged();
    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getRectRessource() const;
};

#endif
