#ifndef CONSOLE_HH_
# define CONSOLE_HH_

# include "EventCallback.hh"
# include "Input.hh"
# include "Scroller.hh"
# include "Container.hh"
# include <list>
# include <vector>

// Console
// Informations - ChatBox history - Administration
// Catching Console key to toggle

class Console : public Layer, public EventCallback
{
  public:
    static const int		MAX_HEIGHT = 512;

  private:
    bool			_display_time;
    bool			_is_visible;
    Theme			*_theme;
    Input			*_input;
    sf::RectangleShape		_bg;
    std::vector<sf::Text *>	_texts;
    sf::Text			_input_desc;
    Scroller			*_scroller;
    Container			*_container;
    int				_pos_start;

    void			inputReleased();
    bool			textEntered(std::string &str);
    void			updateContainer();

  public:
    Console();
    ~Console();

    void			settingChanged();
    void			draw(sf::RenderWindow &win);
    void			setTheme(Theme *theme);

    void			displayTime(bool display);
    bool			isVisible();
    void			toggle(Context);
    void			wheelMoved();
    void			addLog(const std::string &msg, const sf::Color &color);
};

#endif
