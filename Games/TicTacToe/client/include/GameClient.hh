#ifndef GAME_CLIENT_HH_
# define GAME_CLIENT_HH_

# include "AGameClient.hh"

// GameClient - Class Inherited from AGameClientClient

class GameClient : public AGameClient
{
  public:
    GameClient();
    ~GameClient();

    // Ini settings principally
    virtual bool		init();
    virtual void		exit();
    virtual void		run();
    virtual void		playerJoined(ProtocoledPacket &packet);
    virtual void		playerLeft(ProtocoledPacket &packet);

    // Called every frame
    virtual void		update();
    // Waiting Infos from server (Players data, map, ...) - if waiting : return false
    virtual bool		initGame(ProtocoledPacket &packet);
};

#endif
