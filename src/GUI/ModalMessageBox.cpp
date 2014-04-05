#include "GUI/Screen.hh"
#include "GUI/ModalMessageBox.hh"
#include "jag.hh"
#include "Titlebar.hh"

ModalMessageBox::ModalMessageBox(const sf::String &title, Item *desc) :
  Layer(),
  EventCallback(),
  _draw_fog(true),
  _y_button_start(16),
  _has_button(false)
{
  // Escape say goodbye
  catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Escape), [&](Context) {
      Screen::remove(this);
      });

  // Layer take all the space (Modal)
  _rec.left = 0;
  _rec.top = 0;
  _rec.width = Screen::getSize().x;
  _rec.height = Screen::getSize().y;

  letTitlebar(true);

  _theme = jag::getTheme("ModalMessageBox");

  Rect rec = Rect(Screen::getSize().x / 2 - WIDTH / 2, Screen::getSize().y / 2 - HEIGHT / 2, WIDTH, HEIGHT);

  String *g_title = new String(title, jag::getTheme("ModalMessageBoxTitle"));
  rec.height = TITLE_HEIGHT;
  g_title->setBorder(Border::Bottom);
  g_title->setMargin(sf::Vector2i(8, 0));
  g_title->setRect(rec);
  add(g_title);

  rec.top += TITLE_HEIGHT + jag::getTheme("ModalMessageBoxTitle")->size_border;
  rec.height = 300;
  desc->setMargin(sf::Vector2i(8, 20));
  desc->setTheme(_theme);
  desc->setRect(rec);
  rec.height = desc->getRectRessource().height + 40;
  desc->setRect(rec);
  add(desc);

  Rect desc_rec = desc->getRect();
  rec.top = desc_rec.top + desc_rec.height;
  _button_bar.setPosition(g_title->getRect().left, rec.top);
  _button_bar.setSize(sf::Vector2f(rec.width, BUTTON_BAR_HEIGHT));
  _button_bar.setFillColor(jag::getTheme("ModalMessageBoxTitle")->c_background);

  _fog.setPosition(0, 0);
  _fog.setSize(sf::Vector2f(_rec.width, _rec.height));
  _fog.setFillColor(sf::Color(100, 100, 100, 50));
}

ModalMessageBox::~ModalMessageBox()
{
}

void			ModalMessageBox::draw(sf::RenderWindow &window)
{
  if (_draw_fog)
    window.draw(_fog);

  if (_has_button)
    window.draw(_button_bar);

  Layer::draw(window);
}

void			ModalMessageBox::addButton(const sf::String &str, Item::Callback cb)
{
  _has_button = true;

  String	*button = new String(str, jag::getTheme("ModalMessageBoxButton"));
  button->setAlignment(Item::Alignment::Center);
  button->addCallback([&, cb](){ Screen::remove(this); if (cb) { cb(); } });
  button->setBorder(Border::Right);
  button->setRect(Rect(_button_bar.getPosition().x + WIDTH - _y_button_start - BUTTON_WIDTH,
      _button_bar.getPosition().y + BUTTON_HEIGHT / 2,
      BUTTON_WIDTH, BUTTON_HEIGHT));
  add(button);

  _y_button_start += BUTTON_WIDTH + 8;
}

void			ModalMessageBox::drawFog(bool draw)
{
  _draw_fog = draw;
}

void			ModalMessageBox::letTitlebar(bool let)
{
  if (let)
    _rec.top = Titlebar::HEIGHT;
  else
    _rec.top = 0;
}