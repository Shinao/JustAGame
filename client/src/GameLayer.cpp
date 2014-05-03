#include "GameLayer.hh"
#include "String.hh"
#include "Input.hh"

GameLayer::GameLayer() :
  MainMenuItem("GAME")
{
  int	size_item = _rec.width / 3;
  int	x_half = _rec.left + _rec.width / 2 + MARGIN;
  int	x_start = _rec.left;

  // Player name
  String	*text = new String("Player Name", jag::getTheme("ItemSetting"));
  text->setRect(Rect(_rec.left, _y_content, size_item, HEIGHT));
  add(text);
  Input		*input = new Input();
  input->setRect(Rect(x_half, _y_content, size_item, HEIGHT));
  add(input);
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
}

void			GameLayer::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}

void			GameLayer::mouseLeft()
{
  Layer::mouseLeft();
}
