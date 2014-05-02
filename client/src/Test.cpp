#include "Test.hh"
#include "Screen.hh"
#include "String.hh"
#include "Input.hh"
#include "ListItem.hh"
#include "CheckBox.hh"
#include "ModalMessageBox.hh"

Test::Test() :
  Layer::Layer()
{
  _rec = Rect(50, Screen::getSize().y - HEIGHT * 5, 700, 600);;

  Input	*text = new Input();
  text->setRect(Rect(100, _rec.top + 100, Input::INPUT_WIDTH, Input::INPUT_HEIGHT));
  add(text);

  String *btn = new String("Click me");
  btn->setRect(Rect(200, _rec.top, 100, HEIGHT));
  btn->setString("RHLAKJDHAS");
  add(btn, "btn");

  StringArea *area = new StringArea("Lorem ipsum dolar si vis pacem para bellum. Caesar ma grosse bute.");
  area->setRect(Rect(300, _rec.top + 120, 100, HEIGHT));
  add(area);

  ListBox *lb = new ListBox(new String("abcdef"), jag::getTheme("Button"));
  lb->add(new String("heeloo"));
  lb->add(new String("hee1"));
  lb->add(new String("heeloo2"));
  lb->add(new String("he3"));
  lb->add(new String("ASJDHAdsadsdasdasdsad"));
  lb->setRect(Rect(320, _rec.top + 20, 100, 32));
  add(lb, "lb");
  lb->setTooltip("Hello you!");

  // ModalMessageBox *msg = new ModalMessageBox("Connection", new StringArea("LLoading some Game. Please waLoading some Game. Please waLoading some Game. Please waoading some Game. Please wait."));
  // msg->addButton("Hello");
  // msg->addButton("BIIdADJHKASD");

  Table *table = new Table();
  table->setRect(Rect(460, _rec.top, 300, 200));
  table->init(4);
  std::vector<Item *> items;
  items.push_back(new String("1111"));
  items.push_back(new String("222"));
  items.push_back(new String("3333"));
  items.push_back(new String("44444"));
  table->addRow(items);
  items.clear();
  items.push_back(new String("Hey"));
  items.push_back(new String("Macarena"));
  items.push_back(new String("HAIII"));
  items.push_back(new String("!!!!"));
  table->addRow(items);
  items.clear();
  items.push_back(new String("Hey"));
  items.push_back(new String("Macarena"));
  items.push_back(new String("HAIII"));
  items.push_back(new String("!!!!"));
  table->addRow(items);
  add(table);

  ListItem *list = new ListItem(new String("Seewww"), jag::getTheme("ListItem"));
  list->setItemTheme(jag::getTheme("ItemListItem"));
  list->setRect(Rect(460, _rec.top + 250, 100, 50));
  list->add(new String("test"));
  list->add(new String("DASDASDASDASdasdasd"));
  add(list);

  CheckBox *cb = new CheckBox(new String("Check me CHECKME"));
  cb->setRect(Rect(460, _rec.top + 150, 100, 50));
  add(cb);
}

Test::~Test()
{
}

void			Test::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			Test::draw(sf::RenderWindow &window)
{
  Layer::draw(window);
}

void			Test::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}

void			Test::mouseLeft()
{
  Layer::mouseLeft();
}
