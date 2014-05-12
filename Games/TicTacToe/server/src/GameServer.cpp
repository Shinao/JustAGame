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


GameServer::GameServer()
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

void			GameServer::playerJoined(ProtocoledPacket &packet)
{
  // Mandatory - before calling the parrent, create the player
  //
  APlayer	*player = new PlayerServer(); // Change this line by your inherited class
  packet.getClient()->setPlayer(player);
  AGameServer::playerJoined(packet);
  //
  // Do what you want here
}

void			GameServer::playerInitialized(ProtocoledPacket &packet)
{
  // Mandatory - Start the game on the client side
  //
  AGameServer::playerInitialized(packet);
  ProtocoledPacket *init = new ProtocoledPacket(packet.getClient(), Request::InitGame, Network::TCP);
  // Add whatever you want to packet here

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
