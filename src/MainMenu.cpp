#include "MainMenu.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"
#include "Titlebar.hh"
#include "ServerMenu.hh"

MainMenu::MainMenu(Screen &screen) :
  Layer::Layer(screen),
  _layer_menu(NULL)
{
  Rect	rec = Rect(Screen::getSize().x - PADDING - WIDTH, jag::MarginMenu + Titlebar::HEIGHT, WIDTH, HEIGHT);
  _rec = rec;
  _menu = new Menu(Menu::Vertical, rec);
  _menu->setBorder(Border::Left);
  _menu->setMargin(sf::Vector2i(MARGIN, MARGIN / 2));
  _menu->shrinkToFit(true);

  String	*text = new String("SERVERS");
  text->addCallback(std::bind(&MainMenu::cbServer, this));
  _menu->add(text);
  _menu->setPressed(text);
  text = new String("PLAYER");
  text->addCallback(std::bind(&MainMenu::cbPlayer, this));
  _menu->add(text);
  text = new String("KEY BINDINGS");
  text->addCallback(std::bind(&MainMenu::cbKeyBindings, this));
  _menu->add(text);
  text = new String("AUDIO");
  text->addCallback(std::bind(&MainMenu::cbAudio, this));
  _menu->add(text);
  text = new String("VIDEO");
  text->addCallback(std::bind(&MainMenu::cbVideo, this));
  _menu->add(text);
  text = new String("SOURCE CODE");
  text->addCallback(std::bind(&MainMenu::cbSourceCode, this));
  _menu->add(text);

  _menu->update();
}

MainMenu::~MainMenu()
{
  delete _menu;
  _screen.remove(_layer_menu);
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
  _layer_menu = new ServerMenu(_screen);
}

void			MainMenu::cbPlayer()
{
  _screen.remove(_layer_menu);
}

void			MainMenu::cbKeyBindings()
{
}

void			MainMenu::cbAudio()
{
}

void			MainMenu::cbVideo()
{
}

void			MainMenu::cbSourceCode()
{
  Screen::openUrl("https://github.com/Shinao/JustAGame");
}
