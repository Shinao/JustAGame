#include "GUI/EventManager.hh"
#include <iostream>

EventManager::EventManager()
{
  _events.reserve(100);
}

EventManager::~EventManager()
{
  clear();
}

void				EventManager::push(const sf::Event &event)
{
  _events.push_back(event);
}

void				EventManager::clear()
{
  // Clear all action
  _map.clear();
  _events.clear();
}

void				EventManager::invokeCallbacks()
{
  // Checkk all event
  for (auto event : _events)
  {
    // Check if item is equal
    for (auto item : _map)
      if (item.second.action == event)
      {
	item.second.callback(event);
	continue ;
      }
  }

  // Clear automatically
  _events.clear();
}

int				EventManager::add(const Action &action, const Callback &callback)
{
  int	id = _action_id++;

  Event event;
  event.action = action;
  event.callback = callback;
  _map[id] = event;
  return (id);
}

void				EventManager::remove(int id)
{
  _map.erase(id);
}
