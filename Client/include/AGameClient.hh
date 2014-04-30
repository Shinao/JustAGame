#ifndef AGAME_CLIENT_HH_
# define AGAME_CLIENT_HH_

# include "Network.hh"

// AGameClient - Interface to implement for creating a game client
// When implementing a virtual member function non pure, make sure to call the parent
// Use SetServer first before init

# define INI_GROUP	"client"

class AGameClient
{
  protected:
    AGameClient();

    Client		*_server;
    bool		_running;
    std::string		_player_name;

  public:
    virtual ~AGameClient();

    void			setServer(Client *server);
    virtual bool		init();
    virtual void		exit();
    bool			isRunning() const;
    virtual void		run();

    virtual void		update() = 0;
};

#endif


