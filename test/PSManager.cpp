#include "PSManager.hh"
#include <iostream>

PSManager::PSManager()
{
}

PSManager::~PSManager()
{
  clear();
}

void			PSManager::add(PSInfo *info)
{
  auto it = std::find_if(_pss.begin(), _pss.end(), [info] (PSInfo *search)
      { return (info->draw_priority <= search->draw_priority); });

  if (_pss.size() == 0 || it == _pss.end())
    _pss.push_back(info);
  else
    _pss.insert(it, info);
}

void			PSManager::clear()
{
  for (auto system : _pss)
    delete system;
  _pss.clear();
}

void			PSManager::draw(sf::RenderWindow &window)
{
  sf::Time	_elapsed_time = _ps_clock.restart();

  for (auto ps : _pss)
  {
    // Emit new particles and adjust
    ps->system->update(_elapsed_time, _adjustment);

    // Such wow.
    window.draw(*ps->system, sf::BlendAdd);
  }

  _adjustment = sf::Vector2f(0, 0);
}

void			PSManager::cameraMoved(sf::Vector2f &adjustment)
{
  _adjustment += adjustment;
}
