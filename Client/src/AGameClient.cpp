#include "AGameClient.hh"
#include "jag.hh"
#include "Utility/Graphic.hh"

AGameClient::AGameClient() :
  _running(false)
{
}

AGameClient::~AGameClient()
{
}

bool			AGameClient::init()
{
  // Listen to callback
  using namespace std::placeholders;
  Network::addRequest(Request::PlayerJoined, std::bind(&AGameClient::playerJoined, this, _1));
  Network::addRequest(Request::PlayerLeft, std::bind(&AGameClient::playerLeft, this, _1));
  Network::addRequest(Request::Update, std::bind(&AGameClient::updatePlayers, this, _1));

  CSimpleIniA	&ini = jag::getSettings();

  _player_name = ini.GetValue(INI_GROUP, "player_name", "");
  std::string	color = ini.GetValue(INI_GROUP, "player_color", "FFFFFF");
  _player_color = Utility::stringToColor(color);

  // Send Player Info to Server
  ProtocoledPacket	*packet = new ProtocoledPacket(_server, Request::PlayerInfo, Network::Reliable);
  *packet << _player_name << _player_color.r << _player_color.g << _player_color.b;
  Network::send(packet);

  return (true);
}

bool			AGameClient::isRunning() const
{
  return (_running);
}

void			AGameClient::run()
{
  _running = true;
}

void			AGameClient::exit()
{
  _running = false;
}

void			AGameClient::setServer(Client *server)
{
  _server = server;
}

void			AGameClient::updatePlayers(ProtocoledPacket &packet)
{
  // Update players
}

// Implement and create a new player first before calling
void			AGameClient::playerJoined(ProtocoledPacket &packet)
{
  std::string	name;
  sf::Color	color;
  ClientID	id;
  packet >> id >> name >> color.r >> color.g >> color.b;

  Player	*player = packet.getClient()->getPlayer();
  player->setId(id);
  player->setName(name);
  player->setColor(color);
  _players[id] = player;
}

// Remove our player - Call at the end of the implemented method
void			AGameClient::playerLeft(ProtocoledPacket &packet)
{
  ClientID	id;
  packet >> id;
  _players.erase(id);
}
