#ifndef EVENT_CALLBACk_HH_
# define EVENT_CALLBACk_HH_

# include "GUI/EventManager.hh"

class EventCallback
{
  private:
    EventManager			_event;
    std::vector<EventID>		_events;

  public:
    EventCallback(EventManager &event);
    ~EventCallback();

    void				addCallback(const Action &action, const Callback &callback);
    void				clearCallbacks();
};

#endif
