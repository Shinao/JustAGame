#ifndef MODAL_MESSAGEBOX_HH_
# define MODAL_MESSAGEBOX_HH_

# include "EventCallback.hh"
# include "Layer.hh"
# include "String.hh"
# include "StringArea.hh"

// MessageBox - Layer since it should surpass all Drawables

class ModalMessageBox : public Layer, public EventCallback
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
    ModalMessageBox(const sf::String &title, Item *desc);
    ~ModalMessageBox();

    void			letTitlebar(bool let);
    void			drawFog(bool draw);
    void			addButton(const sf::String &str, Item::CallbackGui cb = NULL);

    void			draw(sf::RenderWindow &window);
};

#endif
