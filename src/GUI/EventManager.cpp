#include "GUI/EventManager.hh"
#include <iostream>

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
  _callbacks_events.clear();
  _events.clear();
}

void				EventManager::invokeCallbacks()
{
  // Add pending callbacks
  _callbacks_events.insert(_callbacks_to_add.begin(), _callbacks_to_add.end());
  _callbacks_to_add.clear();
  // Remove pending callbacks
  for (auto to_remove : _callbacks_to_remove)
    _callbacks_events.erase(to_remove);

  // Check all event
  for (auto event : _events)
  {
    for (auto item : _callbacks_events)
      if (item.second.action == event)
	item.second.callback(event);
  }

  _events.clear();
}

EventID				EventManager::add(const Action &action, const CallbackGui &callback)
{
  EventID	id = _action_id++;

  Event event;
  event.action = action;
  event.callback = callback;
  _callbacks_to_add[id] = event;
  return (id);
}

void				EventManager::remove(EventID id)
{
  _callbacks_to_remove.push_back(id);
}
