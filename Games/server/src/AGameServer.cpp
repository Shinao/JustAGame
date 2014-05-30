#include "AGameServer.hh"
#include "LibraryLoader.hh"
#include <fstream>

AGameServer::AGameServer() :
  _running(false)
{
}

AGameServer::~AGameServer()
{
}

bool			AGameServer::init(CSimpleIniA &ini)
{
  _name = ini.GetValue(INI_GROUP, "server_name", "");
  _game_mode = ini.GetValue(INI_GROUP, "game_mode", "");
  _password = ini.GetValue(INI_GROUP, "password", "");
  _admin_password = ini.GetValue(INI_GROUP, "admin_password", "");
  _maximum_players = ini.GetLongValue(INI_GROUP, "maximum_players", -1);

  return (!_name.empty() && !_game_mode.empty() && _maximum_players != -1);
}

// User does not have our game - send library and rsrc
// TODO - Send RSRC folder
// TODO - Thread this time-consuming operation
void			AGameServer::sendGame(ProtocoledPacket &packet)
{
  std::string			lib_path;
  std::ifstream			lib_file;
  bool				win32;
  ProtocoledPacket		*send_game; 

  // Getting library depending on the OS
  packet >> win32;
  lib_path = Network::GAMES_PATH + _game_mode + "/lib" + _game_mode;
  lib_path += (win32 ? ".dll" : ".so");

  // Send it if found or send error
  lib_file.open(lib_path, std::ios_base::in | std::ios_base::ate);
  
  if (!lib_file.is_open())
  {
    send_game = new ProtocoledPacket(packet.getClient(), Request::GetGame, Network::TCP);
    *send_game << lib_path << (sf::Int8) -1;
    Network::send(send_game);
    return ;
  }

  int	file_size = lib_file.tellg();
  int	read = 0;
  lib_file.seekg(0);
  char	data[4096];
  while (lib_file.good())
  {
    send_game = new ProtocoledPacket(packet.getClient(), Request::GetGame, Network::TCP);

    lib_file.read(data, sizeof(data));
    read += sizeof(data);
    *send_game << lib_path << ((sf::Int8) file_size / read) << sizeof(data);
    send_game->append(data, 4096);

    Network::send(send_game);
    send_game = new ProtocoledPacket(packet.getClient(), Request::GetGame, Network::TCP);
  }

  send_game = new ProtocoledPacket(packet.getClient(), Request::GetGame, Network::TCP);
  *send_game << lib_path << (sf::Int8) 100 << (sf::Int32) 0;
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
  // Listen for client broadcast and client connexion/disconnexion
  using namespace std::placeholders;
  Network::getClientAsking(std::bind(&AGameServer::clientAsked, this, _1));
  Network::addRequest(Request::Connexion, std::bind(&AGameServer::clientConnected, this, _1));
  Network::addRequest(Request::PlayerInfo, std::bind(&AGameServer::playerJoined, this, _1));
  Network::addRequest(Request::Disconnexion, std::bind(&AGameServer::clientDisconnected, this, _1));
  Network::addRequest(Request::GetGame, std::bind(&AGameServer::sendGame, this, _1));
  Network::addRequest(Request::Message, std::bind(&AGameServer::messageReceived, this, _1));

  _running = true;

  std::cout << "Server is running" << std::endl;
}

void			AGameServer::exit()
{
  _running = false;
}

void			AGameServer::messageReceived(ProtocoledPacket &packet)
{
  Network::sendToClients(Request::Message, Network::TCP, packet);
}

void			AGameServer::clientAsked(ProtocoledPacket &packet)
{
  // Send info to client 
  ProtocoledPacket	*response = new ProtocoledPacket(NULL, Request::Allo, Network::Unconnected);
  *response << _name << _game_mode << hasPassword() << (sf::Uint8) Network::getClients().size()
    << (sf::Uint8) _maximum_players;
  Network::send(response, packet.getClient()->getIp(), packet.getClient()->getPort());

  std::cout << packet.getClient()->getIp() << ":" << packet.getClient()->getPort()
    << " asked for servers" << std::endl;
}

// Possibly nothing to do here - Player not initialized
void			AGameServer::clientConnected(ProtocoledPacket &packet)
{
  std::cout << "Client " << packet.getClient()->getIp() << ":" << packet.getClient()->getPort() << " connected to server" << std::endl;
}

// Create a new player and link it to the client before calling this method
void			AGameServer::playerJoined(ProtocoledPacket &packet)
{
  APlayer	&player = *packet.getClient()->getPlayer();
  player.setId(packet.getClient()->getId());
  player.setClient(packet.getClient());

  std::string	name;
  sf::Color	color;
  packet >> name >> color.r >> color.g >> color.b;

  if (name.empty())
    name = packet.getClient()->getIp().toString();

  player.setName(name);
  player.setColor(color);
  _players[player.getId()] = &player;

  // Send to all client a new player joined (Yeahh!)
  sf::Packet	new_packet;
  new_packet << packet.getClient()->getId() << name << color.r << color.g << color.b;
  Network::sendToClients(Request::PlayerJoined, Network::Reliable, new_packet);

  std::cout << "Player [" << name << "][" << player.getId() << "] joined the game" << std::endl;
}

// Send to all clients the player who left (Boooh!)
void			AGameServer::clientDisconnected(ProtocoledPacket &packet)
{
  // Client may be not a player
  if (packet.getClient()->getPlayer() != NULL)
  {
    sf::Packet	new_packet;
    new_packet << packet.getClient()->getId();
    Network::sendToClients(Request::PlayerLeft, Network::Reliable, new_packet);

    std::cout << "Player [" << packet.getClient()->getPlayer()->getName() << "]["
      << packet.getClient()->getId() << "] left the game" << std::endl;

    // Call implementation since we have a player
    playerLeft(packet);

    _players.erase(packet.getClient()->getId());
  }
}

// Custom implementation of the Request PlayerLeft since it does not exist
void			AGameServer::playerLeft(ProtocoledPacket &)
{
}
