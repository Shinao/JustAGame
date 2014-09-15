#ifndef GAME_SERVER_HH_
# define GAME_SERVER_HH_

# include "server/AGameServer.hh"
# include "server/TicTacToe/PlayerServer.hh"

// GameServer

// Be aware that this is a example
// The server is actually easy to crash with a custom client
// Example : Not checking if a player left in playerPlayed
// The current client don't let the player play, but with a custom one, it will crash
// The client shouldn't check if the server is legit, but the server always should.

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
    virtual void		playerJoined(ProtocoledPacket &packet);
    virtual void		playerLeft(ProtocoledPacket &packet);

    virtual void		update();
    virtual Version		getVersion();

    // Specific TicTacToe
    void			playerPlayed(ProtocoledPacket &packet);
    bool			checkPlayer(ClientID id);
};

#endif
