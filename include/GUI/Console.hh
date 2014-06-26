#ifndef CONSOLE_HH_
# define CONSOLE_HH_

# include "EventCallback.hh"
# include "Input.hh"
# include "Scroller.hh"
# include <list>
# include <vector>

// Console
// Informations - ChatBox history - Administration
// Catching [²/`] to toggle

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

  public:
    Console();
    ~Console();

    void			settingChanged();
    void			draw(sf::RenderWindow &win);

    void			setTheme(Theme *theme);
    void			displayTime(bool display);
    bool			isVisible();
    void			toggle(Context);
};

#endif
