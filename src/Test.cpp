#include "Test.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"

#include "GUI/Input.hh"

Test::Test(Screen &screen) :
  Layer::Layer(screen)
{
  _rec = Rect(50, Screen::getSize().y - HEIGHT, 100, HEIGHT);;
  _menu = new Menu(Menu::Horizontal, _rec);
  _rec.width = 300;

  Input	*text = new Input(screen.getEventManager());
  _menu->add(text);

  _menu->update();

  String *btn = new String("Click me");
  btn->setRect(Rect(300, _rec.top, 100, HEIGHT));
  btn->setString("RHLAKJDHAS");
  add(btn, "btn");
}

Test::~Test()
{
  delete _menu;
}

void			Test::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);

  if (_menu->getRect().contains(x, y))
    _menu->mouseReleased(x, y);
}

void			Test::draw(sf::RenderWindow &window)
{
  Layer::draw(window);

  _menu->draw(window);
}

void			Test::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);

  if (_menu->getRect().contains(Screen::getCursorPosition()))
    _menu->mouseCaught(x, y);
  else
    _menu->mouseLeft();
}

void			Test::mouseLeft()
{
  Layer::mouseLeft();

  _menu->mouseLeft();
}