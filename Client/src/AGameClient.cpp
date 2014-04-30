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

  // Send Player Name to Server
  _player_name = ini.GetValue(INI_GROUP, "player_name", "");

  return (!_player_name.empty());
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
