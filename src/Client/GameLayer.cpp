#include "GameLayer.hh"
#include "String.hh"
#include "Input.hh"
#include "Sprite.hh"
#include "Utility/Graphic.hh"
#include "SimpleIni.hpp"

GameLayer::GameLayer() :
  MainMenuItem("GAME"),
  _square_color_picker(sf::Quads, 16),
  _tri_color_picker(sf::Quads, 4)
{
  CSimpleIniA	&ini = jag::getSettings();

  // Player Name
  String	*text = new String("Player Name", jag::getTheme("ItemSetting"));
  add(text, "name");
  Input		*input = new Input();
  input->setInput(ini.GetValue(INI_GROUP, "player_name", ""));
  add(input, "inName");

  // Apply button
  text = new String("Apply", jag::getTheme("Button"));
  text->autoRelease(true);
  text->addCallback(std::bind(&GameLayer::applyChanges, this));
  add(text, "apply");

  // Player Color
  text = new String("Player Color", jag::getTheme("ItemSetting"));
  add(text, "color");

  _tri_color_picker[0].color = sf::Color::Red;
  _tri_color_picker[1].color = sf::Color::Red;
  _tri_color_picker[2].color = sf::Color::White;
  _tri_color_picker[3].color = sf::Color::Black;

  sf::Image 	&img = jag::getRessource(jag::RESSOURCE_PATH + "bird.png");
  _tex_bird = new sf::Texture();
  _tex_bird->loadFromImage(img);
  _spr_bird = new sf::Sprite();
  _spr_bird->setTexture(*_tex_bird);
  Sprite	*sprite = new Sprite(_spr_bird);
  add(sprite, "bird");

  // Set the color
  std::string color = ini.GetValue(INI_GROUP, "player_color", "FFFFFF");
  Utility::stringToColor(_player_color, color);
  sprite->applyColor(_player_color);
  _tri_color_picker[0].color = _player_color;
  _tri_color_picker[1].color = _player_color;

  sf::Color	colors[NB_COLOR];
  colors[0] = sf::Color::Red;
  colors[1] = sf::Color::Yellow;
  colors[2] = sf::Color::Green;
  colors[3] = sf::Color::Blue;

  for (int i = 0; i < NB_COLOR; ++i)
  {
    int pos = i * 4;
    _square_color_picker[pos].color = colors[i];
    _square_color_picker[pos + 1].color = colors[i];
    _square_color_picker[pos + 2].color = colors[(i + 1) % NB_COLOR];
    _square_color_picker[pos + 3].color = colors[(i + 1) % NB_COLOR];
  }
}

GameLayer::~GameLayer()
{
}

void			GameLayer::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			GameLayer::draw(sf::RenderWindow &win)
{
  MainMenuItem::draw(win);

  win.draw(_square_color_picker);
  win.draw(_tri_color_picker);
}

void			GameLayer::mousePressed(int x, int y)
{
  Layer::mousePressed(x, y);

  checkColorPickers(x, y);
}

void			GameLayer::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);

  checkColorPickers(x, y);
}

void			GameLayer::checkColorPickers(int x, int y)
{
  // Check our color pickers
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    if (_tri_color_picker.getBounds().contains(x, y))
      setColorPickers(x, y);
    else if (_square_color_picker.getBounds().contains(x, y))
    {
      setColorPickers(x, y);
      _tri_color_picker[0].color = _player_color;
      _tri_color_picker[1].color = _player_color;
    }
  }
}

void			GameLayer::setColorPickers(int x, int y)
{
  sf::Image	image = Screen::getWindow().capture();

  _player_color = image.getPixel(x, y);
  ((Sprite *) _drawables["bird"])->applyColor(_player_color);
}

void			GameLayer::applyChanges()
{
  std::string	hex;
  Utility::colorToString(_player_color, hex);

  jag::getSettings().SetValue(INI_GROUP, "player_name", ((Input *) _drawables["inName"])->getInput().c_str());
  jag::getSettings().SetValue(INI_GROUP, "player_color", hex.c_str());
  jag::getSettings().SaveFile(INI_FILE);
}

void			GameLayer::settingChanged()
{
  MainMenuItem::settingChanged();

  int	size_item = _rec.width / 2 - MARGIN;
  int	x_half = _rec.left + _rec.width / 2 + MARGIN;
  int	y = _y_content + 24;
  int	height_color = 16;
  int	height_tri = 72;
  int	width_tri = WIDTH_COLOR * NB_COLOR;

  _drawables["name"]->setRect(Rect(_rec.left, y, size_item, Input::HEIGHT));
  _drawables["inName"]->setRect(Rect(x_half, y, Input::WIDTH, Input::HEIGHT));
  y += Input::HEIGHT + MARGIN;
  _drawables["apply"]->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 60,
	_menu->getRect().top + _menu->getRect().height + 8, 60, 26));
  _drawables["color"]->setRect(Rect(_rec.left, y + height_tri / 2, size_item, Input::HEIGHT));
  int	x = x_half;
  _tri_color_picker[0].position = sf::Vector2f(x, y);
  _tri_color_picker[1].position = sf::Vector2f(x + (WIDTH_COLOR * NB_COLOR), y);
  _tri_color_picker[2].position = sf::Vector2f(x + (WIDTH_COLOR * NB_COLOR), y + height_tri);
  _tri_color_picker[3].position = sf::Vector2f(x, y + height_tri);
  _drawables["bird"]->setRect(Rect(x + width_tri, y - 8, 100, 100));

  y += height_tri + 2;

  for (int i = 0; i < NB_COLOR; ++i)
  {
    int pos = i * 4;
    _square_color_picker[pos].position = sf::Vector2f(x, y);
    _square_color_picker[pos + 1].position = sf::Vector2f(x, y + height_color);
    _square_color_picker[pos + 2].position = sf::Vector2f(x + WIDTH_COLOR, y + height_color);
    _square_color_picker[pos + 3].position = sf::Vector2f(x + WIDTH_COLOR, y);

    x += WIDTH_COLOR;
  }
}
