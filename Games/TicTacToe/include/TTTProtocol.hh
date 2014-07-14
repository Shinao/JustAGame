#ifndef TTTPROTOCOL_HH_
# define TTT_PROTOCOL_HH_

// Game version - Checking if client/server are on the same page
const sf::Uint8			GAME_VERSION = 1;

typedef		sf::Uint8	Case;

// Request specific of the game TicTacToe
// Specific request start at 100

namespace Request
{
  // Play on case x/y : server <-> client
  const RequestID		PlayOnCase = 101;
}

#endif
