#ifndef GAME_HH_
# define GAME_HH_

# include "AGameClient.hh"

// Game - Class Inherited from AGameClient

class Game : AGameClient
{
  private:

  public:
    Game();
    ~Game();

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



