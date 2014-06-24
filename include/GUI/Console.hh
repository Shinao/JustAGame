#ifndef CONSOLE_HH_
# define CONSOLE_HH_

# include "EventCallback.hh"
# include "Input.hh"
# include <list>
# include <vector>

// Console
// Informations - ChatBox history - Administration
// Catching [²/`] to toggle

class Console : public Layer, public EventCallback
{
  public:
    const int			MARGIN = 32;
    const int			MESSAGES_HEIGHT = 128;
    const int			INPUT_HEIGHT = 34;
    const int			WIDTH = 256;

  private:
    Input			*_input;
    Theme			*_theme;

    bool			_display_time;
    bool			_is_typing;

  public:
    Console();
    ~Console();

    void			settingChanged();
    void			draw(sf::RenderWindow &win);

    void			setTheme(Theme *theme);
    void			displayTime(bool display);
    bool			isTyping();
};

#endif
