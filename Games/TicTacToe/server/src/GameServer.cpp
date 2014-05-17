#include "GameServer.hh"
#include "PlayerServer.hh"

// Mandatory part - Since we are a library we need to send our inherited class to the server
// Thanks polymorphism
extern "C"
{
  AGameServer		*getGame()
  {
    return (new GameServer());
  }
}


GameServer::GameServer() :
  _player1(NULL),
  _player2(NULL)
{
}

GameServer::~GameServer()
{
}

bool			GameServer::init(CSimpleIniA &ini)
{
  // We don't have anything to read in our ini file 
  // So just return our parrent call
  return (AGameServer::init(ini));
}

void			GameServer::exit()
{
  AGameServer::exit();
}

void			GameServer::run()
{
  AGameServer::run();
}

void			GameServer::clientConnected(ProtocoledPacket &packet)
{
  // Mandatory - before calling the parrent, create the player
  //
  APlayer	*player = new PlayerServer(); // Change this line by your inherited class
  packet.getClient()->setPlayer(player);
  AGameServer::clientConnected(packet);
  //
  // Do what you want here

  //
}

void			GameServer::playerInitialized(ProtocoledPacket &packet)
{
  // Mandatory - Start the game on the client side
  //
  AGameServer::playerInitialized(packet);
  ProtocoledPacket *init = new ProtocoledPacket(packet.getClient(), Request::InitGame, Network::TCP);
  // Add whatever you want to packet here

  // TicTacToe - Just tell him if he is the first player (wait for second) or second one (game start)
  // Give him his ID
  *init << packet.getClient()->getId();
  if (_player1 == NULL)
    _player1 = (PlayerServer *) packet.getClient()->getPlayer();
  else
  {
    _player2 = (PlayerServer *) packet.getClient()->getPlayer();
    *init << _player1->getId() << _player1->getName();
  }

  //
  Network::send(init);
  //
}

void			GameServer::playerLeft(ProtocoledPacket &packet)
{
  AGameServer::playerLeft(packet);
}

void			GameServer::update()
{
}
