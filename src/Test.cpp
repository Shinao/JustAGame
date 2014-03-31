#include "Test.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"

#include "GUI/Input.hh"

Test::Test(Screen &screen) :
  Layer::Layer(screen)
{
  _rec = Rect(50, Screen::getSize().y - HEIGHT * 5, 100, 300);;
  _menu = new Menu(Menu::Horizontal, _rec);
  _rec.width = 500;

  Input	*text = new Input(screen.getEventManager());
  _menu->add(text);

  _menu->update();

  String *btn = new String("Click me");
  btn->setRect(Rect(200, _rec.top, 100, HEIGHT));
  btn->setString("RHLAKJDHAS");
  add(btn, "btn");

  ListBox *lb = new ListBox(screen.getEventManager(), new String("abcdef"), jag::getTheme("button"), Item::Alignment::Center);
  lb->add(new String("heeloo"));
  lb->add(new String("hee1"));
  lb->add(new String("heeloo2"));
  lb->add(new String("he3"));
  lb->add(new String("ASJDHAdsadsdasdasdsad"));
  lb->setRect(Rect(350, _rec.top, 100, 32));
  add(lb, "lb");
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
