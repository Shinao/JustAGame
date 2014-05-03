#include "GameLayer.hh"
#include "String.hh"
#include "Input.hh"
#include "Sprite.hh"

GameLayer::GameLayer() :
  MainMenuItem("GAME"),
  _square_color_picker(sf::Quads, 16),
  _tri_color_picker(sf::Triangles, 3)
{
  int	size_item = _rec.width / 2 - MARGIN;
  int	x_half = _rec.left + _rec.width / 2 + MARGIN;
  int	x_start = _rec.left;
  int	y = _y_content;

  // Player Name
  String	*text = new String("Player Name", jag::getTheme("ItemSetting"));
  text->setRect(Rect(_rec.left, y, size_item, Input::HEIGHT));
  add(text);
  Input		*input = new Input();
  input->setRect(Rect(x_half, y, Input::WIDTH, Input::HEIGHT));
  add(input);

  y += Input::HEIGHT + MARGIN;

  // Player Color
  int x_end = x_start + size_item - MARGIN;
  int nb_color = 4;
  int width_color = 36;
  int height_color = 16;
  int height_tri = 72;
  int width_tri = width_color * nb_color;

  text = new String("Player Color", jag::getTheme("ItemSetting"));
  text->setRect(Rect(_rec.left, y + height_tri / 2, size_item, Input::HEIGHT));
  add(text);

  int x = x_half;

  _tri_color_picker[0].position = sf::Vector2f(x, y + height_tri);
  _tri_color_picker[0].color = sf::Color::Black;
  _tri_color_picker[1].position = sf::Vector2f(x + (width_color * nb_color) / 2, y);
  _tri_color_picker[1].color = sf::Color::Red;
  _tri_color_picker[2].position = sf::Vector2f(x + (width_color * nb_color), y + height_tri);
  _tri_color_picker[2].color = sf::Color::White;

  sf::Image 	&img = jag::getRessource("bird.png");
  _tex_bird = new sf::Texture();
  _tex_bird->loadFromImage(img);
  _spr_bird = new sf::Sprite();
  _spr_bird->setTexture(*_tex_bird);
  Sprite	*sprite = new Sprite(_spr_bird);
  sprite->setRect(Rect(x + width_tri, y, 100, 100));
  add(sprite);
  sprite->applyColor(sf::Color::Green);

  y += height_tri + 2;

  sf::Color	colors[nb_color];
  colors[0] = sf::Color::Red;
  colors[1] = sf::Color::Yellow;
  colors[2] = sf::Color::Green;
  colors[3] = sf::Color::Blue;

  for (int i = 0; i < nb_color; ++i)
  {
    int pos = i * 4;
    _square_color_picker[pos].position = sf::Vector2f(x, y);
    _square_color_picker[pos].color = colors[i];
    _square_color_picker[pos + 1].position = sf::Vector2f(x, y + height_color);
    _square_color_picker[pos + 1].color = colors[i];
    _square_color_picker[pos + 2].position = sf::Vector2f(x + width_color, y + height_color);
    _square_color_picker[pos + 2].color = colors[(i + 1) % nb_color];
    _square_color_picker[pos + 3].position = sf::Vector2f(x + width_color, y);
    _square_color_picker[pos + 3].color = colors[(i + 1) % nb_color];

    x += width_color;
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
  Layer::draw(win);

  win.draw(_square_color_picker);
  win.draw(_tri_color_picker);
}

void			GameLayer::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}

void			GameLayer::mouseLeft()
{
  Layer::mouseLeft();
}
