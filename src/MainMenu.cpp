#include "MainMenu.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"
#include "Titlebar.hh"

MainMenu::MainMenu()
{
  Rect	rec = Rect(Screen::getSize().x - PADDING - WIDTH, PADDING + Titlebar::HEIGHT, WIDTH, HEIGHT);
  _rec = rec;
  _menu = new Menu(Menu::Vertical, rec);
  _menu->setBorder(Border::Left);
  _menu->setMargin(sf::Vector2i(MARGIN, MARGIN / 2));
  _menu->shrinkToFit(true);

  String	*text = new String("SERVERS");
  text->addCallback(std::bind(&MainMenu::cbServer, this));
  _menu->add(text);
  text = new String("PLAYER");
  _menu->add(text);
  text = new String("KEY BINDINGS");
  _menu->add(text);
  text = new String("AUDIO");
  _menu->add(text);
  text = new String("VIDEO");
  _menu->add(text);
  text = new String("SOURCE CODE");
  text->addCallback(std::bind(&MainMenu::cbSourceCode, this));
  _menu->add(text);

  _menu->update();
}

MainMenu::~MainMenu()
{
  delete _menu;
}

void			MainMenu::released(int x, int y)
{
  if (_menu->getRect().contains(x, y))
    _menu->clicked();
}

void			MainMenu::draw(sf::RenderWindow &window)
{
  _menu->draw(window);
}

bool			MainMenu::update(sf::RenderWindow &)
{
  return (true);
}

bool			MainMenu::catchMouse()
{
  return (true);
}

void			MainMenu::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);

  if (_menu->getRect().contains(Screen::getCursorPosition()))
    _menu->mouseCaught(x, y);
  else
    _menu->mouseLeft();
}

void			MainMenu::mouseLeft()
{
  Layer::mouseLeft();

  _menu->mouseLeft();
}

void			MainMenu::cbServer()
{
}

void			MainMenu::cbSourceCode()
{
  Screen::openUrl("https://github.com/Shinao/JustAGame");
}
