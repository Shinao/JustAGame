#ifndef TEXT_HH_
# define TEXT_HH_

# include "GUI/Item.hh"

// Text specialization for an iten in a menu

class Text : public Item
{
  private:
    sf::Text			_text;

  public:
    Text();
    ~Text();

    void			setText(const sf::String &text);
    const sf::String		&getText();
    void			setRect(const Rect &rec);

    void			draw(sf::RenderWindow &win);
    void			update();
    void			mouseCaught(int x, int y);
    void			mouseLeft();
};

#endif
