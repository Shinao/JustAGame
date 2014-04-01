#ifndef TEXT_HH_
# define TEXT_HH_

# include "GUI/Item.hh"

// Text specialization for an item in a menu.. or not
// Format the text (..) if iis too big

class String : public Item
{
  private:
    sf::Text			_text;
    sf::String			_text_original;

  public:
    String(const sf::String &text, Theme *theme = jag::getCurrentTheme(), Alignment align = Left, float scale = 1.0f);
    ~String();

    void			setString(const sf::String &text);
    const sf::String		&getString();

    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getRectRessource() const;
    void			designChanged();
};

#endif
