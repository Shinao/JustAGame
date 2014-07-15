#ifndef TEXT_HH_
# define TEXT_HH_

# include "Item.hh"

// Text specialization for an item in a menu.. or not
// Format the text (..) if iis too big

class String : public Item
{
  private:
    sf::Text			_text;
    std::string			_text_original;

  public:
    String(const sf::String &text, Theme *theme = jag::getCurrentTheme(), float scale = 1.0f);
    ~String();

    void			setString(const std::string &text);
    const sf::String		&getString();

    void			setRect(const Rect &rec);
    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getRectRessource() const;
    void			designChanged();
};

#endif
