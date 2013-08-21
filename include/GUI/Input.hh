#ifndef INPUT_HH_
# define INPUT_HH_

# include "GUI/Item.hh"
# include "GUI/EventManager.hh"
# include "GUI/EventCallback.hh"

// Text specialization for an iten in a menu

class Input : public Item, public EventCallback
{
  public:
    const int			PADDING_TEXT = 4;
    const int 			INPUT_THICKNESS = 1;
    const int			INPUT_WIDTH = 124;
    const int			INPUT_HEIGHT = 28;
    const int			CURSOR_BLINK_SPEED = 500;

  private:
    sf::Text			_text;
    sf::RectangleShape		_input;
    sf::Vector2i		_size;
    int				_thickness;

    sf::RectangleShape		_cursor;
    sf::Clock			_cursor_blink;
    bool			_draw_cursor;

  public:
    Input(EventManager &event, Theme *theme = NULL, Alignment align = Left, float scale = 1.0f);
    ~Input();

    void			setInput(const sf::String &text);
    const sf::String		&getInput();
    void			setRect(const Rect &rec);

    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getRectRessource() const;
    void			designChanged();
    void			pressed();
    void			released();
    void			textEntered(Context context);

    const sf::Vector2i		&getSize() const;
    void			setSize(const sf::Vector2i &size);
    int				getThickness() const;
    void			setThickness(int thickness);

    // Callback
    void			clickCallback(Context event);
};

#endif

