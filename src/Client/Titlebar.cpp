#include "Client/Titlebar.hh"
#include "GUI/Screen.hh"
#include "GUI/Sprite.hh"

Titlebar::Titlebar() :
  Layer(Layer::Setting)
{
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
  _menu = new Menu(Menu::Horizontal);
  _menu->setTheme(jag::getTheme("Titlebar"));
  _menu->setMargin(sf::Vector2i(MENU_MARGIN, (MENU_HEIGHT - img_close.getSize().x) / 2));
  _menu->shrinkToFit(true);
  Sprite	*sprite = new Sprite(&_min_spr);
  sprite->setTheme(jag::getTheme("Titlebar"));
  sprite->autoRelease(true);
  sprite->addCallback(std::bind(&Titlebar::minimize, this));
  sprite->setTooltip("Minimize Window");
  _menu->add(sprite);
  sprite = new Sprite(&_res_spr);
  sprite->setTheme(jag::getTheme("Titlebar"));
  sprite->autoRelease(true);
  sprite->addCallback(std::bind(&Titlebar::restore, this));
  sprite->setTooltip("Center Window");
  _menu->add(sprite);
  sprite = new Sprite(&_cross_spr);
  sprite->addCallback(&Screen::closeWindow);
  sprite->setTooltip("Close Window");
  _menu->add(sprite);
  sprite->setTheme(jag::getTheme("TitlebarCross"));

  add(_menu, "menu");

  // Display logo and icon
  _icon_tex.loadFromImage(jag::getRessource("embleme.png"));
  _icon_spr.setTexture(_icon_tex);
  _logo_tex.loadFromImage(jag::getRessource("logo.png"));
  _logo_spr.setTexture(_logo_tex);
}

Titlebar::~Titlebar()
{
}

void			Titlebar::minimize()
{
  _menu->mouseLeft();

  Screen::minimize();
}

void			Titlebar::restore()
{
  _menu->mouseLeft();
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

void			Titlebar::settingChanged()
{
  Rect	rec = Rect(Screen::getSize().x / 2 - jag::CLIENT_WIDTH / 2 + jag::WINDOW_BORDER_SIZE,
      Screen::getSize().y / 2 - jag::CLIENT_HEIGHT / 2 + jag::WINDOW_BORDER_SIZE,
      jag::CLIENT_WIDTH - jag::WINDOW_BORDER_SIZE * 2, HEIGHT);
  _rec = rec;

  // Updating position
  // Update to get the menu size
  _menu->update();
  rec.height = MENU_HEIGHT;
  rec.left = _rec.left + _rec.width - _menu->getRect().width;
  rec.width = _menu->getRect().width;
  _menu->setRect(rec);

  _icon_spr.setPosition(_rec.left, _rec.top);
  _logo_spr.setPosition(Screen::getSize().x / 2 - _logo_spr.getGlobalBounds().width / 2, _rec.top);
}
