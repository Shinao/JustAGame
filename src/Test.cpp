#include "Test.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"

#include "GUI/Input.hh"

Test::Test() :
  Layer::Layer()
{
  _rec = Rect(50, Screen::getSize().y - HEIGHT * 5, 150, 300);;
  _menu = new Menu(Menu::Horizontal, _rec);
  _rec.width = 500;

  Input	*text = new Input();
  text->setRect(Rect(100, _rec.top + 100, Input::INPUT_WIDTH, Input::INPUT_HEIGHT));
  add(text);

  String *btn = new String("Click me");
  btn->setRect(Rect(200, _rec.top, 100, HEIGHT));
  btn->setString("RHLAKJDHAS");
  add(btn, "btn");

  StringArea *area = new StringArea("Lorem ipsum dolar si vis pacem para bellum. Caesar ma grosse bute.");
  area->setRect(Rect(400, _rec.top + 120, 100, HEIGHT));
  add(area);

  ListBox *lb = new ListBox(new String("abcdef"), jag::getTheme("Button"), Item::Alignment::Center);
  lb->add(new String("heeloo"));
  lb->add(new String("hee1"));
  lb->add(new String("heeloo2"));
  lb->add(new String("he3"));
  lb->add(new String("ASJDHAdsadsdasdasdsad"));
  lb->setRect(Rect(420, _rec.top + 20, 100, 32));
  add(lb, "lb");
  lb->setTooltip("Hello you!");

  MessageBox *msg = new MessageBox("Connection", "LLoading some Game. Please waLoading some Game. Please waLoading some Game. Please waoading some Game. Please wait.");
  msg->addButton("Hello");
  msg->addButton("BIIdADJHKASD");
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
