#include "Client/MainMenuItem.hh"
#include "Client/Titlebar.hh"
#include "GUI/Screen.hh"
#include "Client/StatusBar.hh"

MainMenuItem::MainMenuItem(const std::string &name) :
  Layer(Layer::Setting)
{
  _menu = new Menu(Menu::Horizontal, jag::getTheme("HorizontalMenu"));
  _menu->setMargin(sf::Vector2i(MARGIN, 0));

  _title = new String(name);
  _menu->add(_title);
  _menu->setPressed(_title);

  add(_menu, "menu");
}

MainMenuItem::~MainMenuItem()
{
}

void			MainMenuItem::settingChanged()
{
  int	top = jag::MARGIN_MENU + Titlebar::HEIGHT - HEIGHT;

  Rect	rec = Rect(Screen::getSize().x / 2 - jag::CLIENT_WIDTH / 2 + PADDING,
      Screen::getSize().y / 2 - jag::CLIENT_HEIGHT / 2 + top, WIDTH,
      jag::CLIENT_HEIGHT - top - StatusBar::HEIGHT);
  _rec = rec;

  rec.height = HEIGHT;
  _menu->setRect(rec);

  _y_content = HEIGHT + _rec.top + MARGIN * 2;
}
