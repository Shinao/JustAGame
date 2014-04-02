#include "GUI/Screen.hh"
#include "GUI/MessageBox.hh"
#include "jag.hh"

MessageBox::MessageBox(const sf::String &title, const sf::String &desc) :
  Layer::Layer()
{
  // Layer take all the space (Modal)
  _rec.left = 0;
  _rec.top = 0;
  _rec.width = Screen::getSize().x;
  _rec.height = Screen::getSize().y;

  _theme = jag::getTheme("messagebox");

  Rect rec = Rect(Screen::getSize().x / 2 - MESSAGEBOX_WIDTH / 2, Screen::getSize().y / 2 - MESSAGEBOX_HEIGHT / 2, MESSAGEBOX_WIDTH, MESSAGEBOX_HEIGHT);
  _background.setPosition(rec.left, rec.top);
  _background.setSize(sf::Vector2f(rec.width, rec.height));
  _background.setFillColor(_theme->c_background);
  _background.setOutlineColor(_theme->c_border);
  _background.setOutlineThickness(_theme->size_border);

  String *g_title = new String(title, _theme);
  rec.height = TITLE_HEIGHT;
  g_title->setMargin(sf::Vector2i(4, 0));
  g_title->setRect(rec);
  add(g_title);

  StringArea *g_desc = new StringArea(desc, _theme);
  rec.top += TITLE_HEIGHT;
  rec.height = MESSAGEBOX_HEIGHT - STATUS_BAR_HEIGHT - TITLE_HEIGHT;
  g_desc->setMargin(sf::Vector2i(8, 0));
  g_desc->setRect(rec);
  add(g_desc);
}

MessageBox::~MessageBox()
{
}

void			MessageBox::draw(sf::RenderWindow &window)
{
  window.draw(_background);

  Layer::draw(window);
}
