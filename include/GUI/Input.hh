#ifndef INPUT_HH_
# define INPUT_HH_

# include "GUI/Item.hh"

// Text specialization for an iten in a menu

class Input : public Item
{
  public:
    const int 			INPUT_THICKNESS = 1;
    const int			INPUT_WIDTH = 124;
    const int			INPUT_HEIGHT = 28;

  private:
    sf::Text			_text;
    sf::RectangleShape		_input;
    sf::Vector2i		_size;
    int				_thickness;

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

