#ifndef GAME_SERVER_HH_
# define GAME_SERVER_HH_

# include "AGameServer.hh"
# include "PlayerServer.hh"

// GameServer

class GameServer : public AGameServer
{
  private:
    PlayerServer		*_player1;
    PlayerServer		*_player2;

    ClientID			_marks[3][3];
    
  public:
    GameServer();
    ~GameServer();

    virtual bool		init(CSimpleIniA &ini);
    virtual void		exit();
    virtual void		run();
    virtual void		clientConnected(ProtocoledPacket &packet);
    virtual void		playerInitialized(ProtocoledPacket &packet);
    virtual void		playerLeft(ProtocoledPacket &packet);

    virtual void		update();

    // Specific TicTacToe
    void			playerPlayed(ProtocoledPacket &packet);
};

#endif
