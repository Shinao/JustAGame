#ifndef GAME_MANAGER_HH_
# define GAME_MANAGER_HH_

# include "client/AGameClient.hh"
# include "GUI/ChatBox.hh"
# include "GUI/Console.hh"

// Manager current game

namespace GameManager
{
  void				runGame(AGameClient *game);
  bool				isRunning();
  void				exitGame();

  Client			*getServer();
  AGameClient			*getGame();
  ChatBox			*getChatBox();
  Console			*getConsole();
  int				gamesPlayed();
}

#endif
