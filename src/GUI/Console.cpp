#include <sstream>
#include <iomanip>
#include "Console.hh"
#include "Network.hh"
#include "GameManager.hh"

Console::Console()
{
  setTheme(jag::getCurrentTheme());

  _input = new Input();

  using namespace std::placeholders;
  /* catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Return), std::bind(&Console::enterPressed, this, _1)); */
}

Console::~Console()
{
}

void			Console::displayTime(bool display)
{
  _display_time = display;
}

void			Console::settingChanged()
{
  _rec = Rect(MARGIN, Screen::getSize().y - INPUT_HEIGHT - MESSAGES_HEIGHT - MARGIN, WIDTH,
      MESSAGES_HEIGHT + INPUT_HEIGHT);
}

void			Console::draw(sf::RenderWindow &win)
{
  Layer::draw(win);
}

void			Console::setTheme(Theme *theme)
{
  _theme = theme;
}
