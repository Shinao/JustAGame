#ifndef SPRITE_HH_
# define SPRITE_HH_

# include "GUI/Item.hh"
# include <iostream>

// Sprite
// Sprite will change color depending on the color text of the theme

class Sprite : public Item
{
  private:
    sf::Sprite			*_sprite;
    sf::Color			_apply_mask;

  public:
    Sprite(sf::Sprite *sprite, Theme *theme = jag::getTheme("TransparentSprite"), float scale = 1.0f);
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
