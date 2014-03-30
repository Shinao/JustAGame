#include "MainMenu.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"
#include "Titlebar.hh"
#include "KeyBinding.hh"
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
  text->addCallback([] () { Screen::openUrl("https://github.com/Shinao/JustAGame"); });
  _menu->add(text);

  _menu->update();
}

MainMenu::~MainMenu()
{
  delete _menu;
  _screen.remove(_layer_menu);
}

void			MainMenu::mouseReleased(int x, int y)
{
  if (_menu->getRect().contains(x, y))
    _menu->mouseReleased(x, y);
}

void			MainMenu::draw(sf::RenderWindow &window)
{
  // TODO - Create slider
  sf::View view(sf::FloatRect(_rec.left, _rec.top, _rec.width, _rec.height));
  view.setViewport(sf::FloatRect((float) _rec.left / window.getSize().x,
	(float) _rec.top / window.getSize().y, (float) _rec.width / window.getSize().x,
	(float) _rec.height / window.getSize().y));
  window.setView(view);

  _menu->draw(window);

  window.setView(window.getDefaultView());
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

void			MainMenu::cbReleased()
{
  _screen.remove(_layer_menu);
}

void			MainMenu::cbServer()
{
  _layer_menu = new ServerMenu(_screen);
}

void			MainMenu::cbPlayer()
{
}

void			MainMenu::cbKeyBindings()
{
  _layer_menu = new KeyBinding(_screen);
}

void			MainMenu::cbAudio()
{
}

void			MainMenu::cbVideo()
{
}
