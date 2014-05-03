#include "MainMenuItem.hh"
#include "String.hh"
#include "Titlebar.hh"
#include "Screen.hh"

MainMenuItem::MainMenuItem(const std::string &name) :
  Layer::Layer()
{
  int top = jag::MarginMenu + Titlebar::HEIGHT - HEIGHT;
  Rect	rec = Rect(PADDING, top, WIDTH, Screen::getSize().y - top - 100);
  _rec = rec;
  rec.height = HEIGHT;
  _menu = new Menu(Menu::Horizontal, jag::getTheme("HorizontalMenu"));
  _menu->setRect(rec);
  _menu->setMargin(sf::Vector2i(MARGIN, 0));

  String	*text = new String(name);
  _menu->add(text);
  _menu->setPressed(text);
  _menu->update();

  _y_content = HEIGHT + _rec.top + MARGIN * 2;
}

MainMenuItem::~MainMenuItem()
{
}

void			MainMenuItem::draw(sf::RenderWindow &win)
{
  _menu->draw(win);
}
