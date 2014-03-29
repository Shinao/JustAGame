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

  _menu->update();

  addDrawable(_menu, "menu");
}

ServerMenu::~ServerMenu()
{
}

void			ServerMenu::released(int x, int y)
{
  if (_menu->getRect().contains(x, y))
    _menu->clicked();
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
