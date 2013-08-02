#ifndef ACTION_HH_
# define ACTION_HH_

// Class define capabilities to add actions

class Action
{
  protected:
    std::vector<int>		_actions;

  public:
    Action();
    virtual ~Action();
    int				actionId();
};

#endif
