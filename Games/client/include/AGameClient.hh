#ifndef AGAME_CLIENT_HH_
# define AGAME_CLIENT_HH_

# include "Network.hh"

// AGameClient - Interface to implement for creating a game client
// When implementing a virtual member function non pure, make sure to call the parent
// Use setServer first before init
// Function order : AGameClient() -> init() -> initGame() -> run()

# define INI_GROUP	"client"

class AGameClient
{
  protected:
    AGameClient();

    Client			*_server;
    ClientID			_id;
    bool			_running;
    std::string			_player_name;
    sf::Color			_player_color;

    std::map<ClientID, APlayer *>	_players;

  public:
    virtual			~AGameClient();

    virtual void		setServer(Client *server);
    // Ini settings principally
    virtual bool		init();
    virtual void		exit();
    virtual bool		isRunning() const;
    virtual void		run();
    virtual void		updatePlayers(ProtocoledPacket &packet);
    virtual void		playerJoined(ProtocoledPacket &packet);
    virtual void		playerLeft(ProtocoledPacket &packet);

    // Called every frame
    virtual void		update() = 0;
    // Waiting Infos from server (Players data, map, ...) - if waiting : return false
    virtual bool		initGame(ProtocoledPacket &packet) = 0;
};

#endif
