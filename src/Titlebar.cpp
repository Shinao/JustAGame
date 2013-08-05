#include "GUI/Screen.hh"
#include "Titlebar.hh"
#include "GUI/Text.hh"

Titlebar::Titlebar()
{
  Rect	rec = Rect(0, 0, Screen::getWindowSize().x, TITLEBAR_HEIGHT);
  _rec = rec;

  // Getting click
  int id = actionId();
  Screen::getMap()[id] = thor::Action(sf::Mouse::Left, thor::Action::PressOnce);
  Screen::getSystem().connect(id, std::bind(&Titlebar::clicked, this));


  // Generating all items menu
  sf::Image	&img_close = jag::getRessource("close_window.png");
  sf::Image	&img_min = jag::getRessource("minimize_window.png");
  sf::Image	&img_res = jag::getRessource("restore_window.png");

  _cross_tex.loadFromImage(img_close);
  _cross_spr.setTexture(_cross_tex);
  _min_tex.loadFromImage(img_min);
  _min_spr.setTexture(_min_tex);
  _res_tex.loadFromImage(img_res);
  _res_spr.setTexture(_res_tex);

  // Creating menu
  _menu = new HorizontalMenu(_rec);
  _menu->setMargin(8);
  Sprite	*sprite = new Sprite(MINIMIZE_WINDOW, &_min_spr);
  _menu->add(sprite);
  sprite = new Sprite(RESTORE_WINDOW, &_res_spr);
  _menu->add(sprite);
  sprite = new Sprite(CLOSE_WINDOW, &_cross_spr);
  _menu->add(sprite);

  // Updating position
  rec.height = MENU_WIDTH;
  rec.left += Screen::getWindowSize().x - _menu->getRect().width;
  _menu->setRect(rec);
}

Titlebar::~Titlebar()
{
}

void			Titlebar::clicked()
{
  if (_focused && _menu->getRect().contains(Screen::getCursorPosition()))
    _menu->clicked();
}

void			Titlebar::draw(sf::RenderWindow &window)
{
  _menu->draw(window);
}

bool			Titlebar::update(sf::RenderWindow &window)
{
}

bool			Titlebar::catchMouse()
{
  return (true);
}

void			Titlebar::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);

  if (_menu->getRect().contains(Screen::getCursorPosition()))
    _menu->mouseCaught(x, y);
  else
    _menu->mouseLeft();
}

void			Titlebar::mouseLeft()
{
  Layer::mouseLeft();
}
