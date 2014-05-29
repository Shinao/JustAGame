#include "DrawableManager.hh"
#include "Screen.hh"

DrawableManager::DrawableManager() :
  _id(0),
  _drawable_focused(NULL)
{
}

DrawableManager::~DrawableManager()
{
  // Clear Drawables
  for (auto drawable : _drawables)
    delete drawable.second;
  for (auto drawable : _forgot_drawables)
    delete drawable.second;
}

void			DrawableManager::add(Drawable *drawable, std::string name)
{
  _drawables[name] = drawable;
}

void			DrawableManager::add(Drawable *drawable)
{
  _forgot_drawables[_id++] = drawable;
}

void			DrawableManager::draw(sf::RenderWindow &window)
{
  // Draw all Drawables
  for (auto drawable : _drawables)
    drawable.second->draw(window);
  for (auto drawable : _forgot_drawables)
    drawable.second->draw(window);
}

void			DrawableManager::remove(Drawable *drawable)
{
  for (auto search : _forgot_drawables)
    if (search.second == drawable)
    {
      delete search.second;
      _forgot_drawables.erase(search.first);
      return ;
    }
  for (auto search : _drawables)
    if (search.second == drawable)
    {
      delete search.second;
      _drawables.erase(search.first);
    }
}

void			DrawableManager::remove(std::string name)
{
  delete _drawables[name];
  forget(name);
}

void			DrawableManager::forget(Drawable *drawable)
{
  for (auto it = _forgot_drawables.begin(); it != _forgot_drawables.end(); ++it)
    if (it->second == drawable)
      _forgot_drawables.erase(it);
}

Drawable		*DrawableManager::forget(std::string name)
{
  Drawable	*drawable = get(name);

  _drawables.erase(name);

  return (drawable);
}

Drawable		*DrawableManager::get(std::string name)
{
  auto	drawable = _drawables.find(name);

  if (drawable == _drawables.end())
    return (NULL);

  return (drawable->second);
}

void			DrawableManager::mouseCaught(int x, int y)
{
  // Check already focused
  if (_drawable_focused != NULL)
  {
    if (_drawable_focused->getRect().contains(x, y))
    {
      _drawable_focused->mouseCaught(x, y);
      return ;
    }
    else
      _drawable_focused->mouseLeft();
  }

  // Find new one
  for (auto drawable : _drawables)
    if (checkFocus(drawable.second, x, y))
      return ;
  for (auto drawable : _forgot_drawables)
    if (checkFocus(drawable.second, x, y))
      return ;

  // Nothing found
  _drawable_focused = NULL;
}

bool			DrawableManager::checkFocus(Drawable *drawable, int x, int y)
{
  if (drawable->getRect().contains(x, y))
  {
    // Mouse left on already focused
    if (_drawable_focused != NULL)
      _drawable_focused->mouseLeft();

    drawable->mouseCaught(x, y);
    _drawable_focused = drawable;

    return (true);
  }

  return (false);
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

  for (auto drawable : _forgot_drawables)
    if (drawable.second->getRect().contains(x, y))
    {
      drawable.second->mouseReleased(x, y);
      break ;
    }
}

Drawable		*DrawableManager::getDrawableFocused()
{
  return (_drawable_focused);
}

void			DrawableManager::switchDrawables(DrawableManager &manager)
{
  std::map<int, Drawable *>	forgot_drawables;
  std::map<std::string, Drawable *>	drawables;

  forgot_drawables.insert(_forgot_drawables.begin(), _forgot_drawables.end());
  drawables.insert(_drawables.begin(), _drawables.end());

  _forgot_drawables.clear();
  _drawables.clear();
  _forgot_drawables.insert(manager._forgot_drawables.begin(), manager._forgot_drawables.end());
  _drawables.insert(manager._drawables.begin(), manager._drawables.end());

  manager._forgot_drawables.clear();
  manager._drawables.clear();
  manager._forgot_drawables.insert(forgot_drawables.begin(), forgot_drawables.end());
  manager._drawables.insert(drawables.begin(), drawables.end());
}
