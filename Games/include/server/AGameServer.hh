#ifndef AGAME_SERVER_HH_
# define AGAME_SERVER_HH_

# include "Network/Network.hh"
# include "SimpleIni/SimpleIni.hpp"

// AGameServer - Interface to implement for creating a server
// When implementing a virtual member function non pure, make sure to call the parent
// When implementing playerInitialized - Send a Request::initGame with all the infos

# define INI_GROUP	"server"
# define INI_FILE	"rsrc/server.ini"

class AGameServer
{
  private:
    void			clientAsked(ProtocoledPacket &packet);
    void			errorSendGame(Client *client, const std::string &file_path);
    bool			sendFile(Client *client, const std::string &file);

  protected:
    AGameServer();

    bool			_running;
    std::string			_name;
    std::string			_game_mode;
    std::string			_password;
    std::string			_admin_password;
    int				_maximum_players;

    std::map<ClientID, APlayer *>	_players;
    
  public:
    virtual ~AGameServer();

    virtual bool		init(CSimpleIniA &ini);
    virtual void		exit();
    bool			hasPassword() const;
    bool			isRunning() const;
    void			sendGame(ProtocoledPacket &packet);
    virtual void		run();
    void			clientConnected(ProtocoledPacket &packet);
    virtual void		playerJoined(ProtocoledPacket &packet);
    void			clientDisconnected(ProtocoledPacket &packet);
    virtual void		playerLeft(ProtocoledPacket &packet);
    void			messageReceived(ProtocoledPacket &packet);

    virtual void		update() = 0;
    virtual Version		getVersion() = 0;
};

#endif

