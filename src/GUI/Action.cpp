#include "GUI/Action.hh"

Action::Action() {}

Action::Action(const sf::Event::EventType &type)
{
  _type = type;
  _precision = Default;
}

Action::Action(const sf::Event::EventType &type, const sf::Keyboard::Key &key)
{
  _type = type;
  _precision = Keyboard;
}

Action::Action(const sf::Event::EventType &type, const sf::Mouse::Button &button)
{
  _type = type;
  _button = button;
  _precision = Mouse;
}

Action::~Action() {}

bool			Action::operator==(const sf::Event &event)
{
  if (_type != event.type)
    return (false);

  if (_precision == Keyboard)
  {
    if (_key != event.key.code)
      return (false);
  }
  else if (_precision == Mouse)
    if (_button != event.mouseButton.button)
      return (false);

  return (true);
}
