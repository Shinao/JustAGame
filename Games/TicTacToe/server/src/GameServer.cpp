#include "GameServer.hh"
#include "PlayerServer.hh"
#include "TTTProtocol.hh"

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
  if (!AGameServer::init(ini))
    return (false);

  // Force 2 players
  _maximum_players = 2;

  return (true);
}

void			GameServer::exit()
{
  AGameServer::exit();
}

void			GameServer::run()
{
  AGameServer::run();

  using namespace std::placeholders;
  Network::addRequest(Request::PlayOnCase, std::bind(&GameServer::playerPlayed, this, _1));
}

void			GameServer::playerJoined(ProtocoledPacket &packet)
{
  // Mandatory - before calling the parrent, create the player
  //
  APlayer	*player = new PlayerServer(); // Change this line by your inherited class
  packet.getClient()->setPlayer(player);
  AGameServer::playerJoined(packet);
  // Mandatory - Start the game on the client side
  //
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

  // Check if 2 player -> Game start
  if (_players.size() != 2)
    return ;

  // Don't use protocoled packet since we send it to multiple client - it will do it automatically
  sf::Packet	start;
  start << _player1->getId();
  Network::sendToClients(Request::GameStart, Network::TCP, start);
}

void			GameServer::playerLeft(ProtocoledPacket &packet)
{
  AGameServer::playerLeft(packet);

  if (_player1->getClient() == packet.getClient())
    _player1 = _player2;
  _player2 = NULL;
}

void			GameServer::update()
{
}

void			GameServer::playerPlayed(ProtocoledPacket &packet)
{
  std::cout << "Player played " << std::endl;
  Case		x, y;

  packet >> x >> y;

  _marks[x][y] = packet.getClient()->getId();

  // Send to other player its his turn and that player played
  APlayer		*opponent = (packet.getClient()->getPlayer() == _player1 ? _player2 : _player1);
  Client		*client = opponent->getClient();
  ProtocoledPacket	*ppacket = new ProtocoledPacket(client, Request::PlayOnCase, Network::TCP);
  *ppacket << x << y;
  Network::send(ppacket);
}
