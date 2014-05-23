#ifndef GAME_CLIENT_HH_
# define GAME_CLIENT_HH_

# include "AGameClient.hh"

// GameClient - Class Inherited from AGameClientClient
// TicTacToe Sample

class GameClient : public AGameClient
{
  private:
    const int			LINE_SIZE = 16;

    // Graphics
    sf::Texture			_bg_tex;
    sf::Sprite			_bg;
    sf::RectangleShape		_line;
    Rect			_rec_grid;

    // Game info
    ClientID			_opponent_id;
    // Map TicTacToe
    ClientID			_marks[3][3];
    bool			_our_turn;

    void			drawBackground(sf::RenderWindow &win);
    void			drawGrid(sf::RenderWindow &win);

  public:
    GameClient();
    ~GameClient();

    // Ini settings principally
    virtual bool		init();
    // Load everything
    virtual void		run();
    // Unload everything
    virtual void		exit();
    // New player
    virtual void		playerJoined(ProtocoledPacket &packet);
    // Player left
    virtual void		playerLeft(ProtocoledPacket &packet);
    // Waiting Infos from server (Players data, map, ...) - if waiting : return false
    virtual bool		initGame(ProtocoledPacket &packet);
    // Start the game
    void			gameStart(ProtocoledPacket &packet);
    // We lost
    void			playerWon(ProtocoledPacket &packet);
    // We won
    void			playerLost(ProtocoledPacket &packet);
    // Our turn to play
    void			ourTurn(ProtocoledPacket &packet);

    // Called every frame
    virtual void		draw(sf::RenderWindow &win);
    virtual bool		update(sf::RenderWindow &win);

    // Layer events
    virtual void		mouseReleased(int x, int y);
    // Called when configuration changed
    virtual void		settingChanged();
};

#endif
