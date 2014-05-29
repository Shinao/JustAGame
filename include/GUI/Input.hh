#ifndef INPUT_HH_
# define INPUT_HH_

# include "Item.hh"
# include "EventManager.hh"
# include "EventCallback.hh"

#include <iostream>

// Input text

class Input : public Item, public EventCallback
{
  public:
    static const int		PADDING_TEXT = 4;
    static const int		PADDING_CURSOR = 6;
    static const int 		THICKNESS = 1;
    static const int		WIDTH = 124;
    static const int		HEIGHT = 28;
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

    void			updateCursor();
    bool			isShiftPressed();
    void			checkSelection();
    void			updateRendering();
    void			removeSelection();
    void			enterPressed(Context context);


  public:
    Input(Theme *theme = jag::getTheme("Input"), float scale = 1.0f);
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

    virtual void		setRect(const Rect &rec);
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
