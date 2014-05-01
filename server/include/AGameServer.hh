#ifndef AGAME_SERVER_HH_
# define AGAME_SERVER_HH_

# include "Network.hh"
# include "SimpleIni.hpp"

// AGameServer - Interface to implement for creating a server
// When implementing a virtual member function non pure, make sure to call the parent

# define INI_GROUP	"server"
# define INI_FILE	"server.ini"

class AGameServer
{
  private:
    void			clientAsked(ProtocoledPacket &packet);

  protected:
    AGameServer();

    bool			_running;
    std::string			_name;
    std::string			_game_mode;
    std::string			_password;
    int				_maximum_players;

  public:
    virtual ~AGameServer();

    virtual bool		init(CSimpleIniA &ini);
    virtual void		exit();
    bool			hasPassword() const;
    bool			isRunning() const;
    virtual void		run();
    virtual void		playerJoined(ProtocoledPacket &packet);
    virtual void		playerInitialized(ProtocoledPacket &packet);
    virtual void		playerLeft(ProtocoledPacket &packet);

    virtual void		update() = 0;
};

#endif

