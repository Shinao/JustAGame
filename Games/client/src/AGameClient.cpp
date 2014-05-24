#include "AGameClient.hh"
#include "jag.hh"
#include "Utility/Graphic.hh"
#include "Screen.hh"

AGameClient::AGameClient() :
  Layer(Layer::Game, true),
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
  Utility::stringToColor(_player_color, color);

  // Send Player Info to Server
  ProtocoledPacket	*packet = new ProtocoledPacket(_server, Request::PlayerInfo, Network::TCP);
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

  Screen::toggleMode();
  Screen::add(this);

  catchEvent(Action(sf::Event::KeyReleased, sf::Keyboard::Escape), [] (Context) {
      Screen::toggleIGSetting();
      });

  using namespace std::placeholders;
  Network::addRequest(Request::PlayerJoined, std::bind(&AGameClient::playerJoined, this, _1));
  Network::addRequest(Request::PlayerLeft, std::bind(&AGameClient::playerLeft, this, _1));
  Network::addRequest(Request::Update, std::bind(&AGameClient::updatePlayers, this, _1));
}

void			AGameClient::exit()
{
  _running = false;

  Screen::remove(this);
  Screen::toggleMode();
  clearCallbacks();

  // Disconnect if not already disconnected
  Network::disconnect(_server);

  Network::removeRequest(Request::PlayerJoined);
  Network::removeRequest(Request::PlayerLeft);
  Network::removeRequest(Request::Update);
}

void			AGameClient::setServer(Client *server)
{
  _server = server;
}

void			AGameClient::updatePlayers(ProtocoledPacket &packet)
{
  // Update players
  ClientID	nb;
  ClientID	id;
  Ping		ping;

  // Split packet for each player
  packet >> nb;
  for (ClientID i = 0; i < nb; ++i)
  {
    packet >> id >> ping;
    auto it = _players.find(id);

    // Player not found
    if (it == _players.end())
      return ;

    it->second->setPing(ping);
  }
}

// Implement and create a new player first before calling
void			AGameClient::playerJoined(ProtocoledPacket &packet)
{
  std::string	name;
  sf::Color	color;
  ClientID	id;
  packet >> id >> name >> color.r >> color.g >> color.b;

  APlayer	*player = packet.getClient()->getPlayer();
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

void			AGameClient::draw(sf::RenderWindow &)
{
}

bool			AGameClient::update(sf::RenderWindow &)
{
  return (true);
}

void			AGameClient::settingChanged()
{
  // Our layer take all the screen
  _rec = Rect(0, 0, Screen::getSize().x, Screen::getSize().y);
}

void			AGameClient::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			AGameClient::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}
