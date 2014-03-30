#include "GUI/DrawableManager.hh"
#include "GUI/Screen.hh"

DrawableManager::DrawableManager() :
  _drawable_focused(NULL)
{
}

DrawableManager::~DrawableManager()
{
  // Clear Drawables
  for (auto drawable : _drawables)
    delete drawable.second;
}

void			DrawableManager::add(Drawable *drawable, std::string name)
{
  _drawables[name] = drawable;
}

void			DrawableManager::draw(sf::RenderWindow &window)
{
  // Draw all Drawables
  for (auto drawable : _drawables)
    drawable.second->draw(window);
}

Drawable		*DrawableManager::get(std::string name)
{
  return (_drawables[name]);
}

void			DrawableManager::mouseCaught(int x, int y)
{
  // Check already focused
  if (_drawable_focused != NULL && _drawable_focused->getRect().contains(x, y))
  {
      _drawable_focused->mouseCaught(x, y);
      return ;
  }

  // Find new one
  for (auto drawable : _drawables)
    if (drawable.second->getRect().contains(x, y))
    {
      // Mouse left on already focused
      if (_drawable_focused != NULL)
	_drawable_focused->mouseLeft();

      drawable.second->mouseCaught(x, y);
      _drawable_focused = drawable.second;
      break ;
    }
}

void			DrawableManager::mouseLeft()
{
  if (_drawable_focused != NULL)
  {
    _drawable_focused->mouseLeft();
    _drawable_focused = NULL;
  }
}

void			DrawableManager::mouseReleased(int x, int y)
{
  for (auto drawable : _drawables)
    if (drawable.second->getRect().contains(x, y))
    {
      drawable.second->mouseReleased(x, y);
      break ;
    }
}
