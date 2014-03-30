#ifndef EVENT_MANAGER_HH_
# define EVENT_MANAGER_HH_

# include <functional>
# include <map>
# include "GUI/Action.hh"

// EventManager store all the event that the user push then invoke the callbacks if the events match

typedef int EventID;
typedef const sf::Event & Context;
typedef std::function<void (Context)>	Callback;


class EventManager
{
  private:
    struct				Event
    {
      Action				action;
      Callback				callback;
    };

    EventID				_action_id;
    std::vector<sf::Event>		_events;
    std::map<int, Event>		_map;

  public:
    EventManager();
    ~EventManager();
    void				push(const sf::Event &event);
    void				clear();
    void				invokeCallbacks();
    EventID				add(const Action &action, const Callback &callback);
    void				remove(EventID id);
};

#endif
