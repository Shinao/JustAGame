#include "GUI/EventCallback.hh"

EventCallback::EventCallback(EventManager &event) :
  _event(event)
{
}

EventCallback::~EventCallback()
{
  clearCallback();
}

void		EventCallback::addCallback(const Action &action, const Callback &callback)
{
  _events.push_back(_event.add(action, callback));
}

void		EventCallback::clearCallback()
{
  for (auto event : _events)
    _event.remove(event);
}
