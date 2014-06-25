#include <sstream>
#include <iomanip>
#include "Network.hh"
#include "GameManager.hh"
#include "Console.hh"

Console::Console()
{
  setTheme(jag::getCurrentTheme());

  _input = new Input();

  _bg.setPosition(0, 0);
  _input_desc.setString(">");

  using namespace std::placeholders;
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Tilde), std::bind(&Console::toggle, this, _1));
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
  int	height = std::min((int) MAX_HEIGHT, (int) Screen::getSize().y / 4);

  _rec = Rect(0, 0, Screen::getSize().x, height);
  _bg.setSize(sf::Vector2f(Screen::getSize().x, height));
  _input_desc.setPosition(8, height - _input_desc.getCharacterSize() / 2 - Input::HEIGHT / 2);
  _input->setRect(Rect(_input_desc.getCharacterSize() + 24, height - Input::HEIGHT,
      Screen::getSize().x - _input_desc.getCharacterSize() + 24, Input::HEIGHT));
}

void			Console::draw(sf::RenderWindow &win)
{
  if (_is_visible)
    return ;

  Layer::draw(win);
}

void			Console::setTheme(Theme *theme)
{
  _theme = theme;

  _bg.setFillColor(_theme->c_background);
  _input_desc.setCharacterSize(_theme->size_text);
  _input_desc.setColor(_theme->c_text);
  _input_desc.setFont(_theme->f_text);
}

void			Console::toggle(Context)
{
  _is_visible = !_is_visible;
}


bool			Console::isVisible()
{
  return (_is_visible);
}
