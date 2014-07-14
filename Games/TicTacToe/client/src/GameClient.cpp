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
  for (int x = 0; x < 3; ++x)
    for (int y = 0; y < 3; ++y)
      _marks[x][y] = Client::NULL_ID;
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
    _opponent_id = player2_id;
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
  _bg_tex.loadFromImage(jag::getRessource(Network::GAMES_PATH + "TicTacToe/" + Network::RSRC_PATH + "blackboard.jpg"));
  _bg.setTexture(_bg_tex);
  _line.setFillColor(sf::Color::White);
  _font.loadFromFile(Network::GAMES_PATH + "TicTacToe/" + Network::RSRC_PATH + "PWChalk.ttf");

  _our_turn = false;
  
  // Get network callbacks
  using namespace std::placeholders;
  Network::addRequest(Request::GameStart, std::bind(&GameClient::gameStart, this, _1));
  Network::addRequest(Request::PlayerWon, std::bind(&GameClient::playerWon, this, _1));
  Network::addRequest(Request::PlayerLost, std::bind(&GameClient::playerLost, this, _1));
  Network::addRequest(Request::PlayOnCase, std::bind(&GameClient::opponentPlay, this, _1));
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
  AGameClient::draw(win);

  drawBackground(win);
  drawGrid(win);
  drawMarks(win);
  drawTitle(win);
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
    x += case_size - LINE_SIZE / 2;

    _line.setPosition(x, y);
    win.draw(_line);

    x += LINE_SIZE / 2;
  }

  x = Screen::getSize().x / 2;
  y = Screen::getSize().y / 4;

  _line.setSize(sf::Vector2f(Screen::getSize().y / 2, LINE_SIZE));
  for (unsigned i = 0; i < 2; ++i)
  {
    y += case_size - LINE_SIZE / 2;

    _line.setPosition(x, y);
    win.draw(_line);

    y += LINE_SIZE / 2;
  }
}

void			GameClient::gameStart(ProtocoledPacket &packet)
{
  std::cout << "GAME START" << std::endl;

  ClientID	id;
  packet >> id;
  // Check if our turn
  if (id == _id)
    _our_turn = true;

  // Clear old marks
  for (int x = 0; x < 3; ++x)
    for (int y = 0; y < 3; ++y)
      _marks[x][y] = Client::NULL_ID;
}

void			GameClient::playerWon(ProtocoledPacket &)
{
  std::cout << "won" << std::endl;
}

void			GameClient::playerLost(ProtocoledPacket &)
{
  std::cout << "lost" << std::endl;
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
  sf::Uint8	case_x = x * 3 / _rec_grid.width;
  sf::Uint8	case_y = y * 3 / _rec_grid.height;

  // Abort if already a mark on it
  if (_marks[case_x][case_y] != Client::NULL_ID)
    return ;

  _marks[case_x][case_y] = _id;

  // Send to the server where we played - packet automatically deleted
  ProtocoledPacket	*packet = new ProtocoledPacket(_server, Request::PlayOnCase, Network::TCP);
  *packet << case_x << case_y;
  Network::send(packet);

  _our_turn = false;
}

void			GameClient::settingChanged()
{
  AGameClient::settingChanged();

  _rec_grid = Rect(Screen::getSize().x / 2, Screen::getSize().y /  4,
      Screen::getSize().y / 2, Screen::getSize().y / 2);
}

void			GameClient::opponentPlay(ProtocoledPacket &packet)
{
  std::cout << "Opponent played" << std::endl;

  Case	x, y;

  packet >> x >> y;
  _marks[x][y] = _opponent_id;

  _our_turn = true;
}

void			GameClient::drawMarks(sf::RenderWindow &win)
{
  sf::Text	text("X", _font);
  text.setCharacterSize(_rec_grid.width / 4);

  int	padding_x = _rec_grid.width / 3 / 2 - text.getLocalBounds().width / 2;
  int	padding_y = _rec_grid.height / 3 / 2 - text.getLocalBounds().height / 2 - text.getGlobalBounds().top;

  for (int x = 0; x < 3; ++x)
    for (int y = 0; y < 3; ++y)
    {
      if (_marks[x][y] == Client::NULL_ID)
	continue ;

      if (_marks[x][y] == _id)
      {
	text.setColor(sf::Color::Green);
	text.setString("X");;
      }
      else
      {
	text.setColor(sf::Color::Red);
	text.setString("O");;
      }

      text.setPosition(_rec_grid.left + _rec_grid.width / 3 * x + padding_x,
	  _rec_grid.top + _rec_grid.height / 3 * y + padding_y);
      win.draw(text);
    }
}

void			GameClient::drawTitle(sf::RenderWindow &win)
{
  std::string	opponent_name;

  if (_players.size() == 2)
  {
    opponent_name = _players[_opponent_id]->getName();
    std::transform(opponent_name.begin(), opponent_name.end(), opponent_name.begin(), ::toupper);
  }

  std::string	name = _player_name;
  std::transform(name.begin(), name.end(), name.begin(), ::toupper);
  sf::Text	me(name, _font);
  me.setColor(sf::Color::Green);
  me.setCharacterSize(Screen::getSize().y / 12);
  sf::Text	opponent(opponent_name, _font);
  opponent.setCharacterSize(Screen::getSize().y / 12);
  opponent.setColor(sf::Color::Red);
  sf::Text	vs("VS", _font);
  vs.setCharacterSize(Screen::getSize().y / 6);
  vs.setColor(sf::Color::White);

  me.setPosition(Screen::getSize().x / 2 - me.getLocalBounds().width - vs.getLocalBounds().width / 2,
      16 + vs.getCharacterSize() / 2 - me.getCharacterSize() / 2);
  vs.setPosition(Screen::getSize().x / 2 - vs.getLocalBounds().width / 2, 8);
  opponent.setPosition(Screen::getSize().x / 2 + vs.getCharacterSize(),
      16 + vs.getCharacterSize() / 2 - me.getCharacterSize() / 2);

  win.draw(me);
  win.draw(opponent);
  win.draw(vs);
}

Version			GameClient::getVersion()
{
  return (GAME_VERSION);
}
