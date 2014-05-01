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
  // Listen for client broadcast
  using namespace std::placeholders;
  Network::getClientAsking(std::bind(&AGameServer::clientAsked, this, _1));

  _name = ini.GetValue(INI_GROUP, "server_name", "");
  _game_mode = ini.GetValue(INI_GROUP, "game_mode", "");
  _password = ini.GetValue(INI_GROUP, "password", "");
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
}

void			AGameServer::exit()
{
  _running = false;
}

// Send info to client
void			AGameServer::clientAsked(ProtocoledPacket &packet)
{
  ProtocoledPacket	*response = new ProtocoledPacket(NULL, Request::Allo, Network::Unconnected);
  Network::send(response, packet.getClient()->getIp(), Network::CLIENT_PORT);
}
