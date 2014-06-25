#ifndef CHATBOX_HH_
# define CHATBOX_HH_

# include "EventCallback.hh"
# include "Input.hh"
# include <list>
# include <vector>

// ChatBox
// Players messages, information, warning and errors
// Disappear after Timeout - Display Console if you want to see them again
// Catching [Enter] to add a message

class ChatBox : public Layer, public EventCallback
{
  public:
    static sf::Color		ColorPlayer;
    static sf::Color		ColorTime;
    static sf::Color		ColorInfo;
    static sf::Color		ColorWarning;
    static sf::Color		ColorError;
    static int			Timeout;

    static const int		MARGIN = 32;
    static const int		MESSAGES_HEIGHT = 128;
    static const int		INPUT_HEIGHT = 34;
    static const int		WIDTH = 256;

  private:
    struct Message
    {
      std::tm			time;
      sf::Clock			timer;
      std::string		player_name;
      std::string		message;
      sf::Color			color;
      std::vector<sf::Text *>	texts;
      
      Message(const std::string &message, const std::string &player_name, const sf::Color &color);
      ~Message();
    };

    Input			*_input;
    Theme			*_theme;

    std::list<Message *>	_messages;

    bool			_display_time;
    bool			_is_typing;

    void			generateText();
    void			enterPressed(Context context);
    void			inputReleased();
    void			checkTimeout();

  public:
    ChatBox();
    ~ChatBox();

    void			settingChanged();
    void			draw(sf::RenderWindow &win);

    void			setTheme(Theme *theme);
    void			add(const std::string &msg, const std::string &player_name);
    void			add(const std::string &msg, const sf::Color &color);
    void			displayTime(bool display);
    bool			isTyping();
};

#endif
