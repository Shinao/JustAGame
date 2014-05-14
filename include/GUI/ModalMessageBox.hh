#ifndef MODAL_MESSAGEBOX_HH_
# define MODAL_MESSAGEBOX_HH_

# include "EventCallback.hh"
# include "Layer.hh"
# include "String.hh"
# include "StringArea.hh"

// MessageBox - Layer since it should surpass all Drawables

class ModalMessageBox : public Layer, public EventCallback
{
  public:
    typedef std::function<bool ()> CallbackCheck;

  private:
    const static int		WIDTH = 320;
    const static int		HEIGHT = 150;
    const static int		TITLE_HEIGHT = 42;
    const static int		BUTTON_BAR_HEIGHT = 50;
    const static int		BUTTON_HEIGHT = 26;
    const static int		BUTTON_WIDTH = 60;
    const static int		PADDING_BUTTONS = 16;

    sf::RectangleShape		_fog;
    bool			_draw_fog;
    Theme			*_theme;
    sf::RectangleShape		_button_bar;
    int				_y_button_start;
    bool			_has_button;
    std::vector<String *>	_buttons;
    CallbackCheck		_cb_exit;

  public:
    ModalMessageBox(const sf::String &title, Item *desc, bool can_escape = true);
    ~ModalMessageBox();

    void			letTitlebar(bool let);
    void			drawFog(bool draw);
    void			addButton(const sf::String &str, Item::CallbackGui cb = NULL);
    void			clearButtons();
    String			*getButton(int index);
    void			canEscape(bool can_escape);
    void			setDescription(Item *desc);
    void			addExitCallback(CallbackCheck cb);

    void			draw(sf::RenderWindow &window);
};

#endif
