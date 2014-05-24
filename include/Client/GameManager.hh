#ifndef GAME_MANAGER_HH_
# define GAME_MANAGER_HH_

# include "AGameClient.hh"

// Manager current game

namespace GameManager
{
  void				runGame(AGameClient *game);
  bool				isRunning();
  void				exitGame();
}

#endif
