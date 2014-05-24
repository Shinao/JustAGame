#include "GameManager.hh"

namespace GameManager
{
  namespace
  {
    AGameClient			*_game = NULL;
    bool			_running = false;

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
    _game = game;

    using namespace std::placeholders;
    Network::addRequest(Request::Disconnexion, std::bind(&GameManager::serverDisconnected, _1));

    _running = true;
    _game->run();
  }

  bool				isRunning()
  {
    return (_running);
  }

  void				exitGame()
  {
    Network::removeRequest(Request::Disconnexion);

    _game->exit();

    _running = false;
    _game = NULL;
  }
}
