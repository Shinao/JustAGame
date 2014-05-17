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
  // Listen for client broadcast and client connexion/disconnexion
  using namespace std::placeholders;
  Network::getClientAsking(std::bind(&AGameServer::clientAsked, this, _1));
  Network::addRequest(Request::Connexion, std::bind(&AGameServer::clientConnected, this, _1));
  Network::addRequest(Request::PlayerInfo, std::bind(&AGameServer::playerInitialized, this, _1));
  Network::addRequest(Request::Disconnexion, std::bind(&AGameServer::playerLeft, this, _1));
  Network::addRequest(Request::GetGame, std::bind(&AGameServer::sendGame, this, _1));

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
void			AGameServer::clientConnected(ProtocoledPacket &packet)
{
  packet.getClient()->getPlayer()->setId(packet.getClient()->getId());
  std::cout << "connected : " << packet.getClient()->getPlayer() << std::endl;

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
  std::cout << "init : " << &player << std::endl;
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
