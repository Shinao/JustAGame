#ifndef TOOLTIP_HH_
# define TOOLTIP_HH_

# include "Layer.hh"
# include "String.hh"

// Tooltip - Layer since it should surpass all Drawables

class Tooltip : public Layer
{
  private:
    static const int		SpaceFromCursor = 64;
    static const int		StringWidth = 100;
    static const int		StringHeight = 32;
    static const int		BarSize = 2;

    String			*_string;
    sf::RectangleShape		_bar;

  public:
    Tooltip(const sf::String &text, const sf::Vector2i &pos);
    ~Tooltip();

    bool			catchMouse() const;
    void			draw(sf::RenderWindow &window);
};

#endif

