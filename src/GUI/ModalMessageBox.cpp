#include "Screen.hh"
#include "ModalMessageBox.hh"
#include "jag.hh"
#include "Titlebar.hh"

ModalMessageBox::ModalMessageBox(const sf::String &title, Item *desc, bool can_escape) :
  Layer(),
  EventCallback(),
  _draw_fog(true),
  _y_button_start(PADDING_BUTTONS),
  _has_button(false)
{
  canEscape(can_escape);

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
  g_title->setMargin(sf::Vector2i(8, 0));
  g_title->setRect(rec);
  add(g_title, "title");

  setDescription(desc);

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

void			ModalMessageBox::addButton(const sf::String &str, Item::CallbackGui cb)
{
  _has_button = true;

  String	*button = new String(str, jag::getTheme("ModalMessageBoxButton"));
  button->addCallback([&, cb](){
      if (cb)
        cb();

      if (_cb_exit)
      {
        if (_cb_exit())
          Screen::remove(this);
      }
      else
        Screen::remove(this);
    });
  button->setRect(Rect(_button_bar.getPosition().x + WIDTH - _y_button_start - BUTTON_WIDTH,
      _button_bar.getPosition().y + BUTTON_HEIGHT / 2,
      BUTTON_WIDTH, BUTTON_HEIGHT));
  add(button);
  _buttons.push_back(button);

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

void			ModalMessageBox::canEscape(bool can_escape)
{
  clearCallbacks();

  // Escape : say goodbye
  if (can_escape)
    catchEvent(Action(sf::Event::KeyPressed, sf::Keyboard::Escape), [&](Context) {
      if (_cb_exit)
      {
        if (_cb_exit())
          Screen::remove(this);
      }
      else
        Screen::remove(this);
    });
}

void			ModalMessageBox::setDescription(Item *desc)
{
  remove(desc);

  Rect	rec = _drawables["title"]->getRect();
  rec.width = WIDTH;
  rec.top += TITLE_HEIGHT + jag::getTheme("ModalMessageBoxTitle")->size_border;
  rec.height = 300;
  desc->setMargin(sf::Vector2i(8, 20));
  desc->setTheme(_theme);
  desc->setRect(rec);
  rec.height = desc->getRectRessource().height + 40;
  desc->setRect(rec);
  add(desc, "desc");

  Rect desc_rec = desc->getRect();
  rec.top = desc_rec.top + desc_rec.height;
  _button_bar.setPosition(rec.left, rec.top);
  _button_bar.setSize(sf::Vector2f(rec.width, BUTTON_BAR_HEIGHT));
  _button_bar.setFillColor(jag::getTheme("ModalMessageBoxTitle")->c_background);
}

void			ModalMessageBox::clearButtons()
{
  for (auto btn : _buttons)
    remove(btn);

  _buttons.clear();

  _y_button_start = PADDING_BUTTONS;
}

String			*ModalMessageBox::getButton(int index)
{
  return (_buttons[index]);
}

void			ModalMessageBox::addExitCallback(CallbackCheck cb)
{
  _cb_exit = cb;
}
