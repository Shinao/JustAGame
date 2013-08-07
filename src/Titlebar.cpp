#include "GUI/Screen.hh"
#include "Titlebar.hh"
#include "GUI/Text.hh"

Titlebar::Titlebar()
{
  Rect	rec = Rect(0, 0, Screen::getSize().x, TITLEBAR_HEIGHT);
  _rec = rec;

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
  _menu->setTheme(jag::getTheme("titlebar"));
  _menu->setMargin(8);
  Sprite	*sprite = new Sprite(&_min_spr);
  sprite->autoRelease(true);
  sprite->addCallback(&Screen::minimize);
  _menu->add(sprite);
  sprite = new Sprite(&_res_spr);
  sprite->autoRelease(true);
  sprite->addCallback(&Screen::restore);
  _menu->add(sprite);
  sprite = new Sprite(&_cross_spr);
  sprite->setTheme(jag::getTheme("titlebar_cross"));
  sprite->addCallback(&Screen::closeWindow);
  _menu->add(sprite);

  // Updating position
  // Update to get the menu size
  _menu->update();
  rec.height = MENU_WIDTH;
  rec.left += Screen::getSize().x - _menu->getFilledRect().width;
  _menu->setRect(rec);
  _menu->update();
}

Titlebar::~Titlebar()
{
}

void			Titlebar::minimizeWindow()
{
  Screen::minimize();
}

void			Titlebar::restoreWindow()
{
  Screen::restore();
}


void			Titlebar::clicked(int x, int y)
{
  if (_menu->getRect().contains(x, y))
    _menu->clicked();
}

void			Titlebar::draw(sf::RenderWindow &window)
{
  _menu->draw(window);
}

bool			Titlebar::update(sf::RenderWindow &)
{
  return (true);
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

  _menu->mouseLeft();
}
