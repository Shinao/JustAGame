#include "Test.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"

#include "GUI/Input.hh"

Test::Test(Screen &screen) :
  Layer::Layer(screen)
{
  _rec = Rect(50, Screen::getSize().y - HEIGHT, 200, HEIGHT);;
  _menu = new Menu(Menu::Horizontal, _rec);

  Input	*text = new Input(screen.getEventManager());
  _menu->add(text);

  _menu->update();
}

Test::~Test()
{
  delete _menu;
}

void			Test::released(int x, int y)
{
  if (_menu->getRect().contains(x, y))
    _menu->clicked();
}

void			Test::draw(sf::RenderWindow &window)
{
  _menu->draw(window);
}

bool			Test::update(sf::RenderWindow &)
{
  return (true);
}

bool			Test::catchMouse()
{
  return (true);
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
