#include "GUI/Screen.hh"
#include "GUI/MessageBox.hh"
#include "jag.hh"
#include "Titlebar.hh"

MessageBox::MessageBox(const sf::String &title, const sf::String &desc) :
  Layer::Layer(),
  _draw_fog(true),
  _y_button_start(16)
{
  // Layer take all the space (Modal)
  _rec.left = 0;
  _rec.top = 0;
  _rec.width = Screen::getSize().x;
  _rec.height = Screen::getSize().y;

  letTitlebar(true);

  _theme = jag::getTheme("MessageBox");

  Rect rec = Rect(Screen::getSize().x / 2 - WIDTH / 2, Screen::getSize().y / 2 - HEIGHT / 2, WIDTH, HEIGHT);
  _background.setPosition(rec.left, rec.top);
  _background.setSize(sf::Vector2f(rec.width, rec.height));
  _background.setFillColor(_theme->c_background);
  _background.setOutlineColor(_theme->c_border);
  _background.setOutlineThickness(_theme->size_border);

  String *g_title = new String(title, jag::getTheme("MessageBoxTitle"));
  rec.height = TITLE_HEIGHT;
  g_title->setBorder(Border::Bottom);
  g_title->setMargin(sf::Vector2i(8, 0));
  g_title->setRect(rec);
  add(g_title);

  StringArea *g_desc = new StringArea(desc, _theme);
  rec.top += TITLE_HEIGHT + jag::getTheme("MessageBoxTitle")->size_border;
  rec.height = 300;
  g_desc->setMargin(sf::Vector2i(8, 26));
  g_desc->setRect(rec);
  rec.height = g_desc->getRectRessource().height;
  g_desc->setRect(rec);
  add(g_desc);

  _background.setSize(sf::Vector2f(_background.getSize().x, _background.getSize().y + g_desc->getRectRessource().height));

  _fog.setPosition(0, 0);
  _fog.setSize(sf::Vector2f(_rec.width, _rec.height));
  _fog.setFillColor(sf::Color(100, 100, 100, 50));
}

MessageBox::~MessageBox()
{
}

void			MessageBox::draw(sf::RenderWindow &window)
{
  if (_draw_fog)
    window.draw(_fog);

  window.draw(_background);

  Layer::draw(window);
}

void			MessageBox::addButton(const sf::String &str, Item::Callback cb)
{
  String	*button = new String(str, jag::getTheme("MessageBoxButton"));
  button->setAlignment(Item::Alignment::Center);
  button->addCallback([&](){ Screen::remove(this); cb();});
  button->setBorder(Border::Right);
  button->setRect(Rect(_background.getPosition().x + WIDTH - _y_button_start - BUTTON_WIDTH,
      _background.getPosition().y + _background.getSize().y - STATUS_BAR_HEIGHT + BUTTON_HEIGHT / 2,
      BUTTON_WIDTH, BUTTON_HEIGHT));
  add(button);

  _y_button_start += BUTTON_WIDTH + 8;
}

void			MessageBox::drawFog(bool draw)
{
  _draw_fog = draw;
}

void			MessageBox::letTitlebar(bool let)
{
  if (let)
    _rec.top = Titlebar::HEIGHT;
  else
    _rec.top = 0;
}
