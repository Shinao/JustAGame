#ifndef STRINGAREA_HH_
# define STRINGAREA_HH_

# include "Item.hh"
# include <vector>

// StringArea : multi-line string

// TODO - Add line function and make it bold italic or something

class StringArea : public Item
{
  private:
    static const int		LINE_HEIGHT = 2;

    sf::String			_string;
    std::vector<sf::Text *>	_texts;
    void			checkOutOfBounds(int delta);

  public:
    StringArea(const sf::String &str = "", Theme *theme = jag::getCurrentTheme());
    ~StringArea();

    void			updateRendering();
    void			setString(const sf::String &str);

    Rect			getRectRessource() const;
    void			setRect(const Rect &rec);
    void			draw(sf::RenderWindow &win);
    void			update();
    void			designChanged();
};

#endif
