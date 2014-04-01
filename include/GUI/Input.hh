#ifndef INPUT_HH_
# define INPUT_HH_

# include "GUI/Item.hh"
# include "GUI/EventManager.hh"
# include "GUI/EventCallback.hh"

#include <iostream>

// Input text

class Input : public Item, public EventCallback
{
  public:
    static const int		PADDING_TEXT = 4;
    static const int		PADDING_CURSOR = 6;
    static const int 		INPUT_THICKNESS = 1;
    static const int		INPUT_WIDTH = 124;
    static const int		INPUT_HEIGHT = 28;
    static const int		CURSOR_BLINK_SPEED = 750;

  private:
    std::string			_string;
    sf::Text			_text;
    sf::RectangleShape		_input;
    sf::RectangleShape		_selection;
    sf::Vector2i		_size;
    int				_thickness;

    sf::RectangleShape		_cursor;
    sf::Clock			_cursor_blink;
    bool			_draw_cursor;
    int				_cursor_pos;
    int				_cursor_selection;
    sf::Sprite			_render;
    sf::RenderTexture		_render_texture;

    void			updateCursor();
    bool			isShiftPressed();
    void			checkSelection();
    void			updateRendering();
    void			removeSelection();


  public:
    Input(Theme *theme = jag::getTheme("input"), Alignment align = Left, float scale = 1.0f);
    ~Input();

    void			setInput(const std::string &text);
    const std::string		&getInput();

    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getRectRessource() const;
    void			designChanged();
    void			mouseReleased(int x, int y);
    void			released();
    void			textEntered(Context context);

    const sf::Vector2i		&getSize() const;
    void			setSize(const sf::Vector2i &size);
    int				getThickness() const;
    void			setThickness(int thickness);

    // Callback
    void			click(Context event);
    void			goLeft(Context event);
    void			goRight(Context event);
    void			selectAll(Context event);
    void			removeFront(Context event);
    void			removeBack(Context event);
};

#endif

