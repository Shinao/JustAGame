#include "MainMenuItem.hh"
#include "Titlebar.hh"
#include "Screen.hh"
#include "StatusBar.hh"

MainMenuItem::MainMenuItem(const std::string &name) :
  Layer::Layer()
{
  int top = jag::MarginMenu + Titlebar::HEIGHT - HEIGHT;
  Rect	rec = Rect(PADDING, top, WIDTH, Screen::getSize().y - top - StatusBar::HEIGHT);
  _rec = rec;
  rec.height = HEIGHT;
  _menu = new Menu(Menu::Horizontal, jag::getTheme("HorizontalMenu"));
  _menu->setRect(rec);
  _menu->setMargin(sf::Vector2i(MARGIN, 0));

  _title = new String(name);
  _menu->add(_title);
  _menu->setPressed(_title);
  _menu->update();

  _y_content = HEIGHT + _rec.top + MARGIN * 2;

  add(_menu);
}

MainMenuItem::~MainMenuItem()
{
}

void			MainMenuItem::draw(sf::RenderWindow &win)
{
  Layer::draw(win);
}
