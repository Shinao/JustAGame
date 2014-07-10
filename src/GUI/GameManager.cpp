#include "GameManager.hh"

namespace GameManager
{
  namespace
  {
    AGameClient			*_game = NULL;
    ChatBox			*_chatbox = NULL;
    Console			*_console = NULL;
    int				_games_played = 0;

    void			serverDisconnected(ProtocoledPacket &packet);
  }

  namespace
  {
    void			serverDisconnected(ProtocoledPacket &)
    {
      exitGame();
    }
  }

  void				runGame(AGameClient *game)
  {
    ++_games_played;
    _game = game;

    using namespace std::placeholders;
    Network::addRequest(Request::Disconnexion, std::bind(&GameManager::serverDisconnected, _1));

    _game->run();

    _chatbox = new ChatBox;
    _console = new Console;
  }

  bool				isRunning()
  {
    return (_game != NULL);
  }

  void				exitGame()
  {
    Network::removeRequest(Request::Disconnexion);

    _game->exit();
    _game = NULL;
  }

  Client			*getServer()
  {
    return (Network::getClients()[0]);
  }

  AGameClient			*getGame()
  {
    return (_game);
  }

  ChatBox			*getChatBox()
  {
    return (_chatbox);
  }

  Console			*getConsole()
  {
    return (_console);
  }

  int				gamesPlayed()
  {
    return (_games_played);
  }
}
