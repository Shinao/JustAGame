#ifndef EVENT_CALLBACk_HH_
# define EVENT_CALLBACk_HH_

# include "GUI/EventManager.hh"
# include "GUI/Screen.hh"

class EventCallback
{
  private:
    std::vector<EventID>		_events;

  public:
    EventCallback();
    ~EventCallback();

    void				catchEvent(const Action &action, const CallbackGui &callback);
    void				clearCallbacks();
};

#endif
