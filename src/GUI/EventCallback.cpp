#include "GUI/EventCallback.hh"

EventCallback::EventCallback()
{
}

EventCallback::~EventCallback()
{
  clearCallbacks();
}

void		EventCallback::catchEvent(const Action &action, const Callback &callback)
{
  _events.push_back(Screen::getEventManager().add(action, callback));
}

void		EventCallback::clearCallbacks()
{
  for (auto event : _events)
    Screen::getEventManager().remove(event);

  _events.clear();
}
