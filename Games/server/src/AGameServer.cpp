#include "AGameServer.hh"

AGameServer::AGameServer() :
  _running(false)
{
}

AGameServer::~AGameServer()
{
}

bool			AGameServer::init(CSimpleIniA &ini)
{
  // Listen for client broadcast and client connexion/disconnexion
  using namespace std::placeholders;
  Network::getClientAsking(std::bind(&AGameServer::clientAsked, this, _1));
  Network::addRequest(Request::PlayerJoined, std::bind(&AGameServer::playerJoined, this, _1));
  Network::addRequest(Request::PlayerInfo, std::bind(&AGameServer::playerInitialized, this, _1));
  Network::addRequest(Request::Disconnexion, std::bind(&AGameServer::playerLeft, this, _1));

  _name = ini.GetValue(INI_GROUP, "server_name", "");
  _game_mode = ini.GetValue(INI_GROUP, "game_mode", "");
  _password = ini.GetValue(INI_GROUP, "password", "");
  _admin_password = ini.GetValue(INI_GROUP, "admin_password", "");
  _maximum_players = ini.GetLongValue(INI_GROUP, "maximum_players", -1);

  return (!_name.empty() && !_game_mode.empty() && _maximum_players != -1);
}

bool			AGameServer::hasPassword() const
{
  return (!_password.empty());
}

bool			AGameServer::isRunning() const
{
  return (_running);
}

void			AGameServer::run()
{
  _running = true;

  std::cout << "Server is running" << std::endl;
}

void			AGameServer::exit()
{
  _running = false;
}

void			AGameServer::clientAsked(ProtocoledPacket &packet)
{
  // Send info to client 
  ProtocoledPacket	*response = new ProtocoledPacket(NULL, Request::Allo, Network::Unconnected);
  *response << _name << _game_mode << hasPassword() << (sf::Uint8) Network::getClients().size()
    << (sf::Uint8) _maximum_players;
  Network::send(response, packet.getClient()->getIp(), Network::CLIENT_PORT);

  std::cout << "Computer asked for servers" << std::endl;
}

// Create a new player and link it to the client before calling this method
void			AGameServer::playerJoined(ProtocoledPacket &packet)
{
  packet.getClient()->getPlayer()->setId(packet.getClient()->getId());

  std::cout << "Client connected to server" << std::endl;
}

// Call at the beginning
void			AGameServer::playerInitialized(ProtocoledPacket &packet)
{
  std::string	name;
  sf::Color	color;
  packet >> name >> color.r >> color.g >> color.b;

  if (name.empty())
    name = packet.getClient()->getIp().toString();

  APlayer	&player = *packet.getClient()->getPlayer();
  player.setName(name);
  player.setColor(color);

  // Send to all client a new player joined (Yeahh!)
  sf::Packet	new_packet;
  new_packet << packet.getClient()->getId() << name << color.r << color.g << color.b;
  Network::sendToClients(Request::PlayerJoined, Network::Reliable, new_packet);

  std::cout << "Player joined the game" << std::endl;
}

// Send to all clients the player who left (Boooh!)
void			AGameServer::playerLeft(ProtocoledPacket &packet)
{
  // Client may be not a player
  if (packet.getClient()->getPlayer() != NULL)
  {
    sf::Packet	new_packet;
    new_packet << packet.getClient()->getId();
    Network::sendToClients(Request::PlayerLeft, Network::Reliable, new_packet);

    std::cout << "Player left the game" << std::endl;
  }
}
