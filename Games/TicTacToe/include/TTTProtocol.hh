#ifndef TTTPROTOCOL_HH_
# define TTT_PROTOCOL_HH_

typedef		sf::Uint8	Case;

// Request specific of the game TicTacToe
// Specific request start at 100

namespace Request
{
  // Play on case x/y : server <-> client
  const RequestID		PlayOnCase = 101;
}

#endif
