#include "GUI/EventManager.hh"

EventManager::EventManager() :
  _action_id(0)
{
  _events.reserve(100);
}

EventManager::~EventManager()
{
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
  // Check all event
  for (auto event : _events)
  {
    // Check if item is equal
    for (auto item : _map)
      if (item.second.action == event)
      {
	item.second.callback(event);

	// TODO - Remove useless continue ?
	continue ;
      }
  }

  // Clear automatically
  _events.clear();
}

EventID				EventManager::add(const Action &action, const CallbackGui &callback)
{
  EventID	id = _action_id++;

  Event event;
  event.action = action;
  event.callback = callback;
  _map[id] = event;
  return (id);
}

void				EventManager::remove(EventID id)
{
  _map.erase(id);
}
