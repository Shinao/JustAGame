#ifndef MESSAGEBOX_HH_
# define MESSAGEBOX_HH_

# include "GUI/EventCallback.hh"
# include "GUI/Layer.hh"
# include "GUI/String.hh"
# include "GUI/StringArea.hh"

// MessageBox - Layer since it should surpass all Drawables

class MessageBox : public Layer, public EventCallback
{
  private:
    const static int		WIDTH = 320;
    const static int		HEIGHT = 150;
    const static int		TITLE_HEIGHT = 42;
    const static int		BUTTON_BAR_HEIGHT = 50;
    const static int		BUTTON_HEIGHT = 26;
    const static int		BUTTON_WIDTH = 60;

    sf::RectangleShape		_fog;
    bool			_draw_fog;
    Theme			*_theme;
    sf::RectangleShape		_button_bar;
    int				_y_button_start;
    bool			_has_button;

  public:
    MessageBox(const sf::String &title, Item *desc);
    ~MessageBox();

    void			letTitlebar(bool let);
    void			drawFog(bool draw);
    void			addButton(const sf::String &str, Item::Callback cb = NULL);

    void			draw(sf::RenderWindow &window);
};

#endif


