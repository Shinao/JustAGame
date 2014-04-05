#include "MainMenu.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"
#include "Titlebar.hh"
#include "KeyBinding.hh"
#include "ServerMenu.hh"

MainMenu::MainMenu() :
  Layer::Layer(),
  _layer_menu(NULL)
{
  Rect	rec = Rect(Screen::getSize().x - PADDING - WIDTH, jag::MarginMenu + Titlebar::HEIGHT, WIDTH, HEIGHT);
  _rec = rec;
  _menu = new Menu(Menu::Vertical);
  _menu->setRect(_rec);
  _menu->setBorder(Border::Left);
  _menu->setMargin(sf::Vector2i(MARGIN, MARGIN / 2));
  _menu->shrinkToFit(true);

  String *text = new String("SERVERS");
  text->addCallback(std::bind(&MainMenu::cbServer, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
  _menu->add(text);
  _menu->setPressed(text);
  text = new String("PLAYER");
  text->addCallback(std::bind(&MainMenu::cbPlayer, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
  _menu->add(text);
  text = new String("KEY BINDINGS");
  text->addCallback(std::bind(&MainMenu::cbKeyBindings, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
  _menu->add(text);
  text = new String("AUDIO");
  text->addCallback(std::bind(&MainMenu::cbAudio, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
  _menu->add(text);
  text = new String("VIDEO");
  text->addCallback(std::bind(&MainMenu::cbVideo, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
  _menu->add(text);
  text = new String("GitHub [Source]");
  text->addCallback([]() { Screen::openUrl("https://github.com/Shinao/JustAGame"); });
  _menu->add(text);

  _menu->update();

  add(_menu);
}

MainMenu::~MainMenu()
{
  Screen::remove(_layer_menu);
}

void			MainMenu::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);

  Screen::setMoving(false);
}

void			MainMenu::mousePressed(int x, int y)
{
  Layer::mousePressed(x, y);

  if (getDrawableFocused() == NULL)
    Screen::setMoving(true);
}

void			MainMenu::draw(sf::RenderWindow &window)
{
  _menu->draw(window);
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

void			MainMenu::cbReleased()
{
  Screen::remove(_layer_menu);
}

void			MainMenu::cbServer()
{
  _layer_menu = new ServerMenu();
}

void			MainMenu::cbPlayer()
{
}

void			MainMenu::cbKeyBindings()
{
  _layer_menu = new KeyBinding();
}

void			MainMenu::cbAudio()
{
}

void			MainMenu::cbVideo()
{
}
