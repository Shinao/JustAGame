#include <sstream>
#include <iomanip>
#include "ChatBox.hh"
#include "Network.hh"
#include "GameManager.hh"

sf::Color	ChatBox::ColorPlayer = sf::Color::White;
sf::Color	ChatBox::ColorTime = sf::Color::Green;
sf::Color	ChatBox::ColorInfo = sf::Color::Green;
sf::Color	ChatBox::ColorWarning = sf::Color::Yellow;
sf::Color	ChatBox::ColorError = sf::Color::Red;
int		ChatBox::Timeout = 10;

ChatBox::ChatBox() :
  _display_time(false),
  _is_typing(false)
{
  setTheme(jag::getCurrentTheme());

  _input = new Input();

  using namespace std::placeholders;
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Return), std::bind(&ChatBox::enterPressed, this, _1));

  _input->addCallback(std::bind(&ChatBox::inputReleased, this), Drawable::Released);
  _input->setMaxLength(80);
}

ChatBox::~ChatBox()
{
  Network::removeRequest(Request::Message);
}

void			ChatBox::enterPressed(Context)
{
  if (!_is_typing)
  {
    _is_typing = true;
    DrawableManager::add(_input);
    _input->mouseReleased(0, 0);
    return ;
  }
}

void			ChatBox::inputReleased()
{
  DrawableManager::forget(_input);
  _is_typing = false;

  if (_input->getInput().empty())
    return ;

  // Send input into network
  ProtocoledPacket	*packet = new ProtocoledPacket(GameManager::getServer(), Request::Message, Network::TCP);
  *packet << _input->getInput();
  Network::send(packet);

  _input->setInput("");
}

void			ChatBox::draw(sf::RenderWindow &win)
{
  Layer::draw(win);

  for (auto message : _messages)
    for (auto text : message->texts)
      win.draw(*text);

  checkTimeout();
}

void			ChatBox::checkTimeout()
{
  if (!_messages.size())
    return ;

  if (_messages.back()->timer.getElapsedTime().asSeconds() > Timeout)
  {
    // delete _messages.back();
    _messages.pop_back();

    checkTimeout();
  }
}

void			ChatBox::settingChanged()
{
  _rec = Rect(MARGIN, Screen::getSize().y - INPUT_HEIGHT - MESSAGES_HEIGHT - MARGIN, WIDTH,
      MESSAGES_HEIGHT + INPUT_HEIGHT);

  _input->setRect(Rect(_rec.left, _rec.top + MESSAGES_HEIGHT, WIDTH, INPUT_HEIGHT));
}

void			ChatBox::setTheme(Theme *theme)
{
  _theme = theme;
}

void			ChatBox::add(const std::string &msg, const std::string &player_name)
{
  _messages.push_front(new Message(msg, player_name, ColorPlayer));

  generateText();
}

void			ChatBox::add(const std::string &msg, const sf::Color &color)
{
  _messages.push_front(new Message(msg, "", color));

  generateText();
}

void			ChatBox::displayTime(bool display)
{
  _display_time = display;
}

void			ChatBox::generateText()
{
  Message		&msg = **_messages.begin();
  sf::Text		*text = new sf::Text(msg.message, _theme->f_text, _theme->size_text);
  int			x = _rec.left;
  int			y = _rec.top + MESSAGES_HEIGHT;
  int			height_msg = text->getCharacterSize();

  y -= height_msg;
  if (_display_time)
  {
    std::stringstream	ss;
    ss << "[" << std::setw(2) << std::setfill('0') << msg.time.tm_hour << ":"
       << std::setw(2) << std::setfill('0') << msg.time.tm_min << "] ";
    sf::Text		*time = new sf::Text(ss.str(), _theme->f_text, _theme->size_text);
    time->setColor(ColorTime);
    time->setPosition(x, y);
    msg.texts.push_back(time);
    x += time->getGlobalBounds().width;
  }

  if (!msg.player_name.empty())
  {
    sf::Text	*name = new sf::Text(msg.player_name + ": ", _theme->f_text, _theme->size_text);
    name->setColor(ColorTime);
    name->setPosition(x, y);
    msg.texts.push_back(name);
    x += name->getGlobalBounds().width;
  }

  text->setPosition(x, y);
  msg.texts.push_back(text);

  // Move up all previous messages
  for (auto move_up : _messages)
    for (auto txt : move_up->texts)
      txt->move(0, -height_msg);
}

bool			ChatBox::isTyping()
{
  return (_is_typing);
}


// Struct Message in ChatBox class

ChatBox::Message::Message(const std::string &msg,
    const std::string &name, const sf::Color &c) :
  player_name(name),
  message(msg),
  color(c)
{
  std::time_t	now = std::time(0);
  time = *std::localtime(&now);
}

ChatBox::Message::~Message()
{
  for (auto text : texts)
    delete text;
}
