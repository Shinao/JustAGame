#include <sstream>
#include <iomanip>
#include "Network.hh"
#include "GameManager.hh"
#include "Console.hh"

Console::Console() :
  _is_visible(false)
{
  _input = new Input(jag::getTheme("TextConsole"));
  _input->addCallback(std::bind(&Console::inputReleased, this), Drawable::Released);
  _input->setMaxLength(128);
  // _scroller = new Scroller();

  setTheme(jag::getTheme("Console"));

  _bg.setPosition(0, 0);
  _input_desc.setString(">");

  using namespace std::placeholders;
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Tilde), std::bind(&Console::toggle, this, _1));

  for (int i = 0; i < 100; i++)
  {
    sf::Text *text = new sf::Text("I like TO moveee iTdjsjHAEWKLJHE 123hjd |D)*U&", _theme->f_text, 14);
    _texts.push_back(text);
  }
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
  int	height = std::min((int) MAX_HEIGHT, (int) Screen::getSize().y / 3);

  _rec = Rect(0, 0, Screen::getSize().x, height);
  _bg.setSize(sf::Vector2f(Screen::getSize().x, height));
  _input_desc.setPosition(8, height - _input_desc.getCharacterSize() / 2 - Input::HEIGHT / 2);
  _input->setRect(Rect(_input_desc.getCharacterSize() + 8, height - Input::HEIGHT,
      Screen::getSize().x - _input_desc.getCharacterSize() + 8, Input::HEIGHT));
}

void			Console::draw(sf::RenderWindow &win)
{
  if (!_is_visible)
    return ;

  Layer::draw(win);

  win.draw(_bg);
  win.draw(_input_desc);
  _input->draw(win);
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

  GameManager::getChatBox()->enable(!_is_visible);

  if (_is_visible)
    _input->mouseReleased(0, 0);
  else
    _input->released();
}


bool			Console::isVisible()
{
  return (_is_visible);
}

void			Console::inputReleased()
{
  _input->mouseReleased(0, 0);

  _input->setInput("");
}
