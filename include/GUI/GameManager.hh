#ifndef GAME_MANAGER_HH_
# define GAME_MANAGER_HH_

# include "AGameClient.hh"
# include "ChatBox.hh"

// Manager current game

namespace GameManager
{
  void				runGame(AGameClient *game);
  bool				isRunning();
  void				exitGame();

  Client			*getServer();
  AGameClient			*getGame();
  ChatBox			*getChatBox();
}

#endif
