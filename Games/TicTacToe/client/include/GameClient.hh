#ifndef GAME_CLIENT_HH_
# define GAME_CLIENT_HH_

# include "AGameClient.hh"

// GameClient - Class Inherited from AGameClientClient
// TicTacToe Sample

class GameClient : public AGameClient
{
  private:
    const int			LINE_SIZE = 16;
    const int			CASE_SIZE = 64;

    sf::Texture			_bg_tex;
    sf::Sprite			_bg;
    sf::RectangleShape		_line;

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

    // Called every frame
    virtual void		draw(sf::RenderWindow &win);
    virtual bool		update(sf::RenderWindow &win);
};

#endif
