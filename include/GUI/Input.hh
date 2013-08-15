#ifndef TEXT_HH_
# define TEXT_HH_

# include "GUI/Item.hh"

// Text specialization for an iten in a menu

class Input : public Item
{
  private:
    sf::String			_text;

  public:
    Input(Theme *theme = NULL, Alignment align = Left, float scale = 1.0f);
    ~Input();

    void			setInput(const sf::String &text);
    const sf::String		&getInput();
    void			setRect(const Rect &rec);

    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getRectRessource() const;
    void			designChanged();
};

#endif

