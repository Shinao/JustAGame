#include "GameLayer.hh"
#include "Screen.hh"
#include "Titlebar.hh"
#include "String.hh"
#include "Table.hh"
#include "ModalMessageBox.hh"

GameLayer::GameLayer() :
  Layer::Layer()
{
  int top = jag::MarginMenu + Titlebar::HEIGHT - HEIGHT;
  Rect	rec = Rect(PADDING, top, WIDTH, Screen::getSize().y - top - 100);
  _rec = rec;
  rec.height = HEIGHT;
  _menu = new Menu(Menu::Horizontal, jag::getTheme("HorizontalMenu"));
  _menu->setRect(rec);
  _menu->setMargin(sf::Vector2i(MARGIN, 0));

  String	*text = new String("GAME");
  _menu->add(text);
  _menu->setPressed(text);
  _menu->update();
}

GameLayer::~GameLayer()
{
}

void			GameLayer::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			GameLayer::draw(sf::RenderWindow &win)
{
  _menu->draw(win);
}

void			GameLayer::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);

}

void			GameLayer::mouseLeft()
{
  Layer::mouseLeft();

}

