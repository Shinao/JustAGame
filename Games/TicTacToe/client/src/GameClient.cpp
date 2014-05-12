#include "GameClient.hh"
#include "PlayerClient.hh"

// Mandatory part - Since we are a library we need to send our inherited class to the client
// Thanks polymorphism
extern "C"
{
  AGameClient		*getGame()
  {
    return (new GameClient());
  }
}


GameClient::GameClient()
{
}

GameClient::~GameClient()
{
}

// The ini is available in jag::getSettings()
bool		GameClient::init()
{
  // We don't have anything to read in our ini file 
  // So just return our parrent call
  return (AGameClient::init());
}

void		GameClient::exit()
{
  AGameClient::exit();
}

void		GameClient::run()
{
  AGameClient::run();
}

void		GameClient::playerJoined(ProtocoledPacket &packet)
{
  // Mandatory - before calling the parrent, create the player
  //
  ClientID	id;
  packet >> id << id;
  APlayer	*player = new PlayerClient(); // Change this line by your inherited class
  _players[id] = player;

  AGameClient::playerJoined(packet);
  //
  // Do whatever you want here

  //
}

void		GameClient::playerLeft(ProtocoledPacket &packet)
{
  AGameClient::playerLeft(packet);
}

void		GameClient::update()
{
}

bool		GameClient::initGame(ProtocoledPacket &packet)
{
  return (true);
}
