#include "GameClient.hh"
#include "PlayerClient.hh"
#include "Screen.hh"
#include "TTTProtocol.hh"

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
  _opponent_id = player->getId();
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
  _bg_tex.loadFromImage(jag::getRessource("Games/TicTacToe/blackboard.jpg"));
  _bg.setTexture(_bg_tex);
  _line.setFillColor(sf::Color::White);

  _our_turn = true;
  
  // Get network callbacks
  using namespace std::placeholders;
  Network::addRequest(Request::GameStart, std::bind(&GameClient::gameStart, this, _1));
  Network::addRequest(Request::PlayerWon, std::bind(&GameClient::playerWon, this, _1));
  Network::addRequest(Request::PlayerLost, std::bind(&GameClient::playerLost, this, _1));
  Network::addRequest(Request::YourTurn, std::bind(&GameClient::ourTurn, this, _1));
}

void			GameClient::exit()
{
  Network::removeRequest(Request::GameStart);
  Network::removeRequest(Request::PlayerWon);
  Network::removeRequest(Request::PlayerLost);

  AGameClient::exit();
}

void			GameClient::draw(sf::RenderWindow &win)
{
  Layer::draw(win);

  drawBackground(win);
  drawGrid(win);
}

bool			GameClient::update(sf::RenderWindow &win)
{
  return (Layer::update(win));
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

void			GameClient::drawGrid(sf::RenderWindow &win)
{
  int	x = _rec_grid.left;
  int	y = _rec_grid.top;

  _line.setSize(sf::Vector2f(LINE_SIZE, Screen::getSize().y / 2));
  int	case_size = _line.getSize().y / 3;
  for (unsigned i = 0; i < 2; ++i)
  {
    x += case_size + LINE_SIZE;

    _line.setPosition(x, y);
    win.draw(_line);
  }

  x = Screen::getSize().x / 2;
  y = Screen::getSize().y / 4;

  _line.setSize(sf::Vector2f(Screen::getSize().y / 2, LINE_SIZE));
  for (unsigned i = 0; i < 2; ++i)
  {
    y += case_size + LINE_SIZE;

    _line.setPosition(x, y);
    win.draw(_line);
  }
}

void			GameClient::gameStart(ProtocoledPacket &packet)
{
  // Clear old marks
  for (int x = 0; x < 3; ++x)
    for (int y = 0; y < 3; ++y)
      _marks[x][y] = Client::NULL_ID;
}

void			GameClient::playerWon(ProtocoledPacket &packet)
{
  std::cout << "won" << std::endl;
}

void			GameClient::playerLost(ProtocoledPacket &packet)
{
  std::cout << "lost" << std::endl;
}

void			GameClient::ourTurn(ProtocoledPacket &packet)
{
  _our_turn = true;
}

void			GameClient::mouseReleased(int x, int y)
{
  AGameClient::mouseReleased(x, y);

  if (!_our_turn)
    return ;

  // Check which case we clicked
  if (!_rec_grid.contains(x, y))
    return ;

  x -= _rec_grid.left;
  y -= _rec_grid.top;
  int	case_x = x / _rec_grid.width;
  int	case_y = y / _rec_grid.height;

  std::cout << "play on " << case_x << " / " << case_y << std::endl;
}

void			GameClient::settingChanged()
{
  AGameClient::settingChanged();

  _rec_grid = Rect(Screen::getSize().x / 2, Screen::getSize().y /  2,
      Screen::getSize().y / 2 + 2 * LINE_SIZE, Screen::getSize().y / 2 + 2 * LINE_SIZE);
}
