#include "GUI/EventCallback.hh"

EventCallback::EventCallback(EventManager &event) :
  _event(event)
{
}

EventCallback::~EventCallback()
{
  clearCallbacks();
}

void		EventCallback::catchEvent(const Action &action, const Callback &callback)
{
  _events.push_back(_event.add(action, callback));
}

void		EventCallback::clearCallbacks()
{
  for (auto event : _events)
    _event.remove(event);

  _events.clear();
}
