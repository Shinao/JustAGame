#include "Client/MainMenu.hh"
#include "GUI/Screen.hh"
#include "Client/Titlebar.hh"
#include "Client/InputLayer.hh"
#include "Client/ServerMenu.hh"
#include "Client/GameLayer.hh"
#include "Client/Multimedia.hh"
#include "Client/About.hh"
#include "GUI/GameManager.hh"

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
  Rect	rec = Rect(Screen::getSize().x / 2 + jag::CLIENT_WIDTH / 2 - PADDING - WIDTH,
      Screen::getSize().y / 2 - jag::CLIENT_HEIGHT / 2 + jag::MARGIN_MENU + Titlebar::HEIGHT,
      WIDTH, HEIGHT);
  _rec = rec;

  _menu->setRect(_rec);

  if (!GameManager::gamesPlayed())
    return ;

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
