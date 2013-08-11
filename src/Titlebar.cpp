#include "Titlebar.hh"
#include "GUI/Screen.hh"
#include "GUI/Sprite.hh"

Titlebar::Titlebar()
{
  Rect	rec = Rect(jag::WindowBorderSize, jag::WindowBorderSize,
      		Screen::getSize().x - jag::WindowBorderSize * 2, HEIGHT);
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
  _menu->setBorder(Border::Down);
  _menu->setTheme(jag::getTheme("titlebar"));
  _menu->setMargin(8);
  Sprite	*sprite = new Sprite(&_min_spr);
  sprite->autoRelease(true);
  sprite->addCallback(std::bind(&Titlebar::minimize, this));
  _menu->add(sprite);
  sprite = new Sprite(&_res_spr);
  sprite->autoRelease(true);
  sprite->addCallback(std::bind(&Titlebar::restore, this));
  _menu->add(sprite);
  sprite = new Sprite(&_cross_spr);
  sprite->setTheme(jag::getTheme("titlebar_cross"));
  sprite->addCallback(&Screen::closeWindow);
  _menu->add(sprite);

  // Updating position
  // Update to get the menu size
  _menu->update();
  rec.height = MENU_WIDTH;
  rec.left = _rec.left + _rec.width - _menu->getFilledRect().width;
  rec.width = _menu->getFilledRect().width;
  _menu->setRect(rec);
  _menu->update();

  // Display logo and icon
  _icon_tex.loadFromImage(jag::getRessource("icon.png"));
  _icon_spr.setTexture(_icon_tex);
  _icon_spr.setPosition(8, 4);
  _logo_tex.loadFromImage(jag::getRessource("logo.png"));
  _logo_spr.setTexture(_logo_tex);
  _logo_spr.setPosition(Screen::getSize().x / 2 - _logo_spr.getGlobalBounds().width / 2, 0);
}

Titlebar::~Titlebar()
{
  delete _menu;
}

void			Titlebar::minimize()
{
  // Fix no event send when window minimized and lost focus
  _menu->mouseLeft();

  Screen::minimize();
}

void			Titlebar::restore()
{
  // Fix no event send when window change position and mouse left
  _menu->mouseLeft();
  sf::Mouse::setPosition(sf::Mouse::getPosition());

  Screen::restore();
}

void			Titlebar::pressed(int x, int y)
{
  if (!_menu->getRect().contains(x, y))
    Screen::setMoving(true);
}

void			Titlebar::released(int x, int y)
{
  if (_menu->getRect().contains(x, y))
    _menu->clicked();
  else
    Screen::setMoving(false);
}

void			Titlebar::draw(sf::RenderWindow &window)
{
  _menu->draw(window);
  window.draw(_logo_spr);
  window.draw(_icon_spr);
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
