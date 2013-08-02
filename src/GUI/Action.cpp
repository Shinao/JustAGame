#include "GUI/Screen.hh"
#include "GUI/Action.hh"

Action::Action()
{
}

Action::~Action()
{
  auto			&map = Screen::getMap();

  for (int i = 0; i < _actions.size(); ++i)
    map.removeAction(i);
}

int			Action::actionId()
{
  int			id = Screen::actionId();

  _actions.push_back(id);
  return (id);
}
