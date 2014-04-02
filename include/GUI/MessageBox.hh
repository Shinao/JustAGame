#ifndef MESSAGEBOX_HH_
# define MESSAGEBOX_HH_

# include "GUI/Layer.hh"
# include "GUI/String.hh"
# include "GUI/StringArea.hh"

// MessageBox - Layer since it should surpass all Drawables

class MessageBox : public Layer
{
  private:
    const static int		MESSAGEBOX_WIDTH = 320;
    const static int		MESSAGEBOX_HEIGHT = 130;
    const static int		TITLE_HEIGHT = 42;
    const static int		STATUS_BAR_HEIGHT = 50;
    const static int		BUTTON_HEIGHT = 26;
    const static int		BUTTON_WIDTH = 60;

    sf::RectangleShape		_fog;
    bool			_draw_fog;
    Theme			*_theme;
    sf::RectangleShape		_background;
    int				_y_button_start;

  public:
    MessageBox(const sf::String &title, const sf::String &desc);
    ~MessageBox();

    void			drawFog(bool draw);
    void			addButton(const sf::String &str, Item::Callback cb = NULL);

    void			draw(sf::RenderWindow &window);
};

#endif


