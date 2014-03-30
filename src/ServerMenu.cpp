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

  add(_menu, "menu");
}

ServerMenu::~ServerMenu()
{
}
