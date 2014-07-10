#include "MainMenu.hh"
#include "Screen.hh"
#include "Titlebar.hh"
#include "InputLayer.hh"
#include "ServerMenu.hh"
#include "GameLayer.hh"
#include "Multimedia.hh"
#include "About.hh"
#include "GameManager.hh"

MainMenu::MainMenu() :
  Layer(Layer::Setting),
  _launched(false),
  _layer_menu(NULL)
{
  _menu = new Menu(Menu::Vertical, jag::getTheme("VerticalMenu"));
  _menu->setMargin(sf::Vector2i(MARGIN, MARGIN / 2));
  _menu->shrinkToFit(true);

  String *text = new String("SERVERS");
  text->addCallback(std::bind(&MainMenu::cbServer, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
  _menu->add(text);
  _menu->setPressed(text);
  text = new String("GAME");
  text->addCallback(std::bind(&MainMenu::cbGame, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
  _menu->add(text);
  text = new String("INPUT");
  text->addCallback(std::bind(&MainMenu::cbInput, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
  _menu->add(text);
  text = new String("MULTIMEDIA");
  text->addCallback(std::bind(&MainMenu::cbMultimedia, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
  _menu->add(text);
  text = new String("ABOUT");
  text->addCallback(std::bind(&MainMenu::cbAbout, this));
  text->addCallback(std::bind(&MainMenu::cbReleased, this), Item::Released);
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

void			MainMenu::cbGame()
{
  _layer_menu = new GameLayer();
}

void			MainMenu::cbInput()
{
  _layer_menu = new InputLayer();
}

void			MainMenu::cbMultimedia()
{
  _layer_menu = new Multimedia();
}

void			MainMenu::cbAbout()
{
  _layer_menu = new About();
}

void			MainMenu::settingChanged()
{
  Rect	rec = Rect(Screen::getSize().x / 2 + jag::ClientWidth / 2 - PADDING - WIDTH,
      Screen::getSize().y / 2 - jag::ClientHeight / 2 + jag::MarginMenu + Titlebar::HEIGHT,
      WIDTH, HEIGHT);
  _rec = rec;

  _menu->setRect(_rec);

  // TODO - need to check if game exited
  if (!_launched)
  {
    _launched = true;
    return ;
  }

  // Adding Disconnect button while ingame
  if (GameManager::isRunning())
  {
    _disconnect = new String("DISCONNECT");
    _disconnect->addCallback([] { GameManager::exitGame(); });
    _menu->add(_disconnect);
    _menu->update();
    _disconnect->setTheme(jag::getTheme("Red"));
  }
  else
  {
    _menu->remove(_disconnect);
    delete _disconnect;
    _menu->setIndexState(1, Drawable::Pressed);
    _menu->update();
  }
}
