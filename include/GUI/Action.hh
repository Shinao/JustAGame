#ifndef ACTION_HH_
# define ACTION_HH_

# include <SFML/Window.hpp>

// Class define capabilities to add actions

struct Action
{
  private:
    sf::Event::EventType	_type;
    sf::Keyboard::Key		_key;
    sf::Mouse::Button		_button;

  public:
    enum
    {
      Mouse,
      Keyboard,
      Default
    }				_precision;

    Action();
    Action(const sf::Event::EventType &type);
    Action(const sf::Event::EventType &type, const sf::Keyboard::Key &key);
    Action(const sf::Event::EventType &type, const sf::Mouse::Button &button);
    ~Action();
    bool			operator==(const sf::Event &event);
};

#endif
