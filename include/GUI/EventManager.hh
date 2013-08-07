#ifndef EVENT_MANAGER_HH_
# define EVENT_MANAGER_HH_

# include <SFML/Window.hpp>
# include <functional>
# include <map>
# include "GUI/Action.hh"

// EventManager store all the event that the user push then invoke the callbacks if the events match

typedef const sf::Event & Context;

class EventManager
{
  private:
    struct				Event
    {
      Action				action;
      std::function<void (Context)>	callback;
    };

    int					_action_id;
    std::vector<sf::Event>		_events;
    std::map<int, Event>		_map;

  public:
    EventManager();
    ~EventManager();
    void				push(const sf::Event &event);
    void				clear();
    void				invokeCallbacks();
    int					add(const Action &action,
					const std::function<void (Context)> &callback);
    void				remove(int id);
};

#endif
