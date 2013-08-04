#include "GUI/Screen.hh"
#include "Titlebar.hh"
#include "GUI/Text.hh"

Titlebar::Titlebar()
{
  _rec = Rect(0, 0, Screen::getWindow().getSize().x, TITLEBAR_HEIGHT);

  // Getting click
  int id = actionId();
  Screen::getMap()[id] = thor::Action(sf::Mouse::Left, thor::Action::PressOnce);
  Screen::getSystem().connect(id, std::bind(&Titlebar::clicked, this));


  // Generating all items menu
  sf::Image			&img = jag::getRessource("close_window.png");

  _cross_tex.loadFromImage(img);
  _cross_spr.setTexture(_cross_tex);

  // Creating menu
  _menu = new HorizontalMenu(_rec);
  Sprite			*sprite = new Sprite(CLOSE_WINDOW, &_cross_spr);
  _menu->add(sprite);
}

Titlebar::~Titlebar()
{
}

void			Titlebar::clicked()
{
  if (_focused)
  {
  }
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
}

void			Titlebar::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}

void			Titlebar::mouseLeft()
{
  Layer::mouseLeft();
}
