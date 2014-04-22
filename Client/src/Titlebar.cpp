#include "Titlebar.hh"
#include "Screen.hh"
#include "Sprite.hh"

Titlebar::Titlebar() :
  Layer::Layer()
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
  Menu *menu = new Menu(Menu::Horizontal);
  menu->setBorder(Border::None);
  menu->setTheme(jag::getTheme("Titlebar"));
  menu->setMargin(sf::Vector2i(MENU_MARGIN, (MENU_HEIGHT - img_close.getSize().x) / 2));
  menu->shrinkToFit(true);
  Sprite	*sprite = new Sprite(&_min_spr);
  sprite->autoRelease(true);
  sprite->addCallback(std::bind(&Titlebar::minimize, this));
  sprite->setTooltip("Minimize Window");
  menu->add(sprite);
  sprite = new Sprite(&_res_spr);
  sprite->autoRelease(true);
  sprite->addCallback(std::bind(&Titlebar::restore, this));
  sprite->setTooltip("Center Window");
  menu->add(sprite);
  sprite = new Sprite(&_cross_spr);
  sprite->setTheme(jag::getTheme("TitlebarCross"));
  sprite->addCallback(&Screen::closeWindow);
  sprite->setTooltip("Close Window");
  menu->add(sprite);

  // Updating position
  // Update to get the menu size
  menu->update();
  rec.height = MENU_HEIGHT;
  rec.left = _rec.left + _rec.width - menu->getRect().width;
  rec.width = menu->getRect().width;
  menu->setRect(rec);
  menu->update();

  add(menu, "menu");

  // Display logo and icon
  _icon_tex.loadFromImage(jag::getRessource("embleme.png"));
  _icon_spr.setTexture(_icon_tex);
  _icon_spr.setPosition(8, jag::WindowBorderSize);
  _logo_tex.loadFromImage(jag::getRessource("logo.png"));
  _logo_spr.setTexture(_logo_tex);
  _logo_spr.setPosition(Screen::getSize().x / 2 - _logo_spr.getGlobalBounds().width / 2, 0);
}

Titlebar::~Titlebar()
{
}

void			Titlebar::minimize()
{
  // Fix no event send when window minimized and lost focus
  get("menu")->mouseLeft();

  Screen::minimize();
}

void			Titlebar::restore()
{
  // Fix no event send when window change position and mouse left
  get("menu")->mouseLeft();
  sf::Mouse::setPosition(sf::Mouse::getPosition());

  Screen::restore();
}

void			Titlebar::mousePressed(int x, int y)
{
  Layer::mousePressed(x, y);

  Screen::setMoving(true);
}

void			Titlebar::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);

  Screen::setMoving(false);
}

void			Titlebar::draw(sf::RenderWindow &window)
{
  Layer::draw(window);

  window.draw(_logo_spr);
  window.draw(_icon_spr);
}
