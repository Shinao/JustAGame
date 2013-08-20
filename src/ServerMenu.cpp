#include "ServerMenu.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"
#include "Titlebar.hh"

#include "GUI/Input.hh"

ServerMenu::ServerMenu(Screen &screen) :
  Layer::Layer(screen)
{
  Rect	rec = Rect(PADDING, jag::MarginMenu + Titlebar::HEIGHT - HEIGHT, WIDTH, HEIGHT);
  _rec = rec;
  _menu = new Menu(Menu::Horizontal, rec);
  _menu->setBorder(Border::Down);
  _menu->setMargin(sf::Vector2i(MARGIN, 0));

  String	*text = new String("INTERNET");
  _menu->add(text);
  text = new String("LOCAL");
  _menu->add(text);

  _menu->add(new Input(_screen.getEventManager()));

  _menu->update();
}

ServerMenu::~ServerMenu()
{
  delete _menu;
}

void			ServerMenu::released(int x, int y)
{
  if (_menu->getRect().contains(x, y))
    _menu->clicked();
}

void			ServerMenu::draw(sf::RenderWindow &window)
{
  _menu->draw(window);
}

bool			ServerMenu::update(sf::RenderWindow &)
{
  return (true);
}

bool			ServerMenu::catchMouse()
{
  return (true);
}

void			ServerMenu::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);

  if (_menu->getRect().contains(Screen::getCursorPosition()))
    _menu->mouseCaught(x, y);
  else
    _menu->mouseLeft();
}

void			ServerMenu::mouseLeft()
{
  Layer::mouseLeft();

  _menu->mouseLeft();
}

bool			ServerMenu::textEntered(const std::string &str)
{
  return (_menu->textEntered(str));
}
