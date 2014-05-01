#include "AGameClient.hh"
#include "jag.hh"

AGameClient::AGameClient() :
  _running(false)
{
}

AGameClient::~AGameClient()
{
}

bool			AGameClient::init()
{
  CSimpleIniA	&ini = jag::getSettings();

  _player_name = ini.GetValue(INI_GROUP, "player_name", "");

  // Send Player Name to Server
  ProtocoledPacket	*packet = new ProtocoledPacket(_server, Request::Name, Network::TCP);
  *packet >> _player_name;
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
