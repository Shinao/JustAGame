#ifndef AGAME_CLIENT_HH_
# define AGAME_CLIENT_HH_

# include "Network.hh"

// AGameClient - Interface to implement for creating a game client
// When implementing a virtual member function non pure, make sure to call the parent
// Use SetServer first before init
// Function order : AGameClient() -> init() -> initGame() -> run()

# define INI_GROUP	"client"

class AGameClient
{
  protected:
    AGameClient();

    Client			*_server;
    bool			_running;
    std::string			_player_name;
    sf::Color			_player_color;

    std::map<ClientID, APlayer *>	_players;

  public:
    virtual ~AGameClient();

    void			setServer(Client *server);
    virtual bool		init();
    virtual void		exit();
    bool			isRunning() const;
    virtual void		run();
    void			updatePlayers(ProtocoledPacket &packet);
    virtual void		playerJoined(ProtocoledPacket &packet);
    virtual void		playerLeft(ProtocoledPacket &packet);

    // Called every frame
    virtual void		update() = 0;
    // Get Infos from server (Players data, map, ...) - If waiting for another packet : return false
    virtual bool		initGame(ProtocoledPacket &packet) = 0;
};

#endif


