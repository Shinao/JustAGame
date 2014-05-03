#include "Multimedia.hh"
#include "Screen.hh"
#include "Titlebar.hh"
#include "String.hh"
#include "Table.hh"
#include "ModalMessageBox.hh"

Multimedia::Multimedia() :
  Layer::Layer()
{
  int top = jag::MarginMenu + Titlebar::HEIGHT - HEIGHT;
  Rect	rec = Rect(PADDING, top, WIDTH, Screen::getSize().y - top - 100);
  _rec = rec;
  rec.height = HEIGHT;
  _menu = new Menu(Menu::Horizontal, jag::getTheme("HorizontalMenu"));
  _menu->setRect(rec);
  _menu->setMargin(sf::Vector2i(MARGIN, 0));

  String	*text = new String("MULTIMEDIA");
  _menu->add(text);
  _menu->setPressed(text);
  _menu->update();
}

Multimedia::~Multimedia()
{
}

void			Multimedia::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			Multimedia::draw(sf::RenderWindow &win)
{
  _menu->draw(win);
}

void			Multimedia::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);

}

void			Multimedia::mouseLeft()
{
  Layer::mouseLeft();

}


