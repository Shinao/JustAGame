#include "GameClient.hh"
#include "PlayerClient.hh"
#include "Screen.hh"
#include "Ressources.hh"

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
bool			GameClient::init()
{
  // We don't have anything to read in our ini file 
  // So just return our parrent call
  return (AGameClient::init());
}

bool			GameClient::initGame(ProtocoledPacket &packet)
{
  ClientID	player2_id = Client::NULL_ID;
  std::string	player2_name;

  // Get IDs
  packet >> _id >> player2_id >> player2_name;

  // Add us to the list of players
  PlayerClient	*player = new PlayerClient();
  player->setId(_id);
  player->setName(_player_name);
  _players[_id] = player;

  // We are not the first player
  if (player2_id != Client::NULL_ID)
  {
    player = new PlayerClient();
    player->setId(player2_id);
    player->setName(player2_name);
    _players[player2_id] = player;
  }

  return (true);
}

void			GameClient::playerJoined(ProtocoledPacket &packet)
{
  // Mandatory - before calling the parrent, create the player
  //
  PlayerClient	*player = new PlayerClient(); // Change this line by your inherited class
  packet.getClient()->setPlayer(player); // Stock our player temporally

  AGameClient::playerJoined(packet); // Our player now have an name, id, color...
  //
  // Do whatever you want here

  //
}

void			GameClient::playerLeft(ProtocoledPacket &packet)
{
  AGameClient::playerLeft(packet);
}

void			GameClient::run()
{
  AGameClient::run();

  // Window is set properly - load ressources
  jag::createRessourceFromArray("blackboard", blackboard.pixel_data, blackboard.width, blackboard.height);
  _bg_tex.loadFromImage(jag::getRessource("blackboard"));
  _bg.setTexture(_bg_tex);
}

void			GameClient::exit()
{
  AGameClient::exit();
}

void			GameClient::draw(sf::RenderWindow &win)
{
  drawBackground(win);
}

bool			GameClient::update(sf::RenderWindow &)
{
  return (true);
}

void			GameClient::drawBackground(sf::RenderWindow &win)
{
  // Draw background on all the screen
  unsigned	x = 0, y;

  // Repeat for full width
  while (x < Screen::getSize().x)
  {
    y = 0;

    // Repeat for full height 
    while (y < Screen::getSize().y)
    {
      _bg.setPosition(x, y);
      win.draw(_bg);
      y += _bg.getLocalBounds().height;
    }

    x += _bg.getLocalBounds().width;
  }
}
