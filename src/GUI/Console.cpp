#include <sstream>
#include <iomanip>
#include "Network.hh"
#include "GameManager.hh"
#include "Console.hh"

Console::Console() :
  _is_visible(false),
  _pos_start(0)
{
  using namespace std::placeholders;

  _input = new Input(jag::getTheme("TextConsole"));
  _input->addCallback(std::bind(&Console::inputReleased, this), Drawable::Released);
  _input->setCallbackInput(std::bind(&Console::textEntered, this, std::placeholders::_1));
  _input->setMaxLength(128);
  _container = new Container;
  _container->setRect(Rect(0, Input::HEIGHT, Screen::getSize().x, 0));
  _scroller = new Scroller(_container);
  _scroller->setCallbackWheel(std::bind(&Console::wheelMoved, this));

  setTheme(jag::getTheme("Console"));

 _bg.setPosition(0, 0);
  _input_desc.setString(">");

  sf::Keyboard::Key	key_console = jag::getKeyFromValue(jag::getSettings().GetValue(INI_GROUP, "key_console", "Unknown"));
  catchEvent(Action(sf::Event::KeyPressed, key_console), std::bind(&Console::toggle, this, _1));
}

Console::~Console()
{
  for (auto text : _texts)
    delete text;
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
  _input_desc.setPosition(8, Input::HEIGHT / 2 - _input_desc.getCharacterSize() / 2);
  _input->setRect(Rect(_input_desc.getCharacterSize() + 8, 0,
      Screen::getSize().x - _input_desc.getCharacterSize() + 8, Input::HEIGHT));
  updateContainer();
  _scroller->setRect(Rect(0, Input::HEIGHT, Screen::getSize().x, height - Input::HEIGHT));

  wheelMoved();
}

void			Console::draw(sf::RenderWindow &win)
{
  if (!_is_visible)
    return ;

  Layer::draw(win);

  win.draw(_bg);
  win.draw(_input_desc);
  _input->draw(win);
  _scroller->draw(win);

  Screen::scissor(_rec);
  int y = Input::HEIGHT;
  for (int i = _pos_start; i >= 0 && i < (int) _texts.size(); --i)
  {
    _texts[i]->setPosition(8, y);
    win.draw(*_texts[i]);
    y += _input_desc.getCharacterSize();

    if (y > _rec.top + _rec.height)
      break ;
  }
  Screen::undoScissor();
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
  {
    _input->mouseReleased(0, 0);
    _scroller->mouseCaught(0, 0);
    updateContainer();
    
    return ;
  }

  _input->released();
  _scroller->mouseLeft();
}

bool			Console::isVisible()
{
  return (_is_visible);
}

void			Console::inputReleased()
{
  if (_is_visible)
  {
    addLog(_input->getInput(), ChatBox::MessageLog);

    _input->mouseReleased(0, 0);
    _input->setInput("");
  }
}

bool			Console::textEntered(std::string &str)
{
  if (str[0] == '`')
    return (false);

  return (true);
}

void			Console::wheelMoved()
{
  int	y_padding = _container->getRect().top - Input::HEIGHT;

  if (y_padding > 0)
  {
    _pos_start = _texts.size() - 1;
    return ;
  }
  
  _pos_start = std::abs(((float) y_padding / _container->getRect().height) * _texts.size());
  _pos_start = _texts.size() - _pos_start - 1;
}

void			Console::updateContainer()
{
  _container->setRect(Rect(_container->getRect().left, _container->getRect().top, Screen::getSize().x, _texts.size() * _theme->size_text));
  _scroller->drawableUpdated();
}

void			Console::addLog(const std::string &msg, const sf::Color &color)
{
  sf::Text *text = new sf::Text(msg, _theme->f_text, _theme->size_text);
  text->setColor(color);
  _texts.push_back(text);

  if (_is_visible)
  {
    updateContainer();
    wheelMoved();
  }
}
