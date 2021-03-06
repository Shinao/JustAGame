#include "Client/StatusBar.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"

const int MAX_LATENCY = 1500;
const int NUMBER_CYCLE = 5;

// void		latency(BridgeThread *bridge);

StatusBar::StatusBar() :
  Layer(Layer::Setting),
  _latency(-1)
{
  _good = sf::Color(63, 146, 210);
  _okay = sf::Color(255, 154, 2);
  _bad = sf::Color(200, 100, 100);

  String	*text = new String("Loading", jag::getTheme("Ping"));
  text->setTooltip("Latency from google");
  add(text, "ping");

  text = new String("LATENCY", jag::getTheme("Transparent"));
  text->setTooltip("Latency from google");
  add(text, "latency");

  _bridge = new BridgeThread;
  _bridge->running = true;
  _bridge->latency = -1;
      using namespace std::placeholders;
  _thread = new sf::Thread(std::bind(&StatusBar::latency, this));
  _thread->launch();
}

StatusBar::~StatusBar()
{
  _bridge->running = false;

  // Terminate thread because fuck it (But mainly because he has timeout)
  _thread->terminate();
  _thread->wait();

  delete _bridge;
}

void			StatusBar::latency()
{
  sf::TcpSocket		pinger;
  sf::Clock		timer;
  long			latency;
  char			rsp[4096];
  size_t		len;
  BridgeThread		*bridge = _bridge;

  pinger.setBlocking(true);
  while (bridge->running)
  {
    // Getting i packet before having the latency
    latency = 0;
    for (int i = 0; i < NUMBER_CYCLE; ++i)
    {
      timer.restart();

      if (pinger.connect("google.com", 80, sf::milliseconds(MAX_LATENCY)) == sf::Socket::Done)
      {
	// Get HEAD - fastest command
	pinger.send("HEAD\n\r", 6);

	if (pinger.receive(rsp, 4096, len) == sf::Socket::Done)
	  latency += timer.getElapsedTime().asMilliseconds();
	else
	  latency += MAX_LATENCY;
      }
      else
	latency += MAX_LATENCY;

      pinger.disconnect();
    }

    bridge->latency = latency / NUMBER_CYCLE;
    sf::sleep(sf::milliseconds(3000 - bridge->latency));
  }
}

bool			StatusBar::update(sf::RenderWindow &)
{
  if (_bridge->latency != _latency)
  {
    _latency = _bridge->latency;
    sf::Color new_color;

    if (_latency < 100)
      new_color = _good;
    else if (_latency < 300)
      new_color = _okay;
    else
      new_color = _bad;

    _drawables["ping"]->getTheme()->c_border = new_color;
    _drawables["ping"]->getTheme()->c_border_focused = new_color;
    _drawables["ping"]->getTheme()->c_border_pressed = new_color;

    std::ostringstream	ostr;
    ostr << _latency;
    ((String *) _drawables["ping"])->setString(ostr.str());
    _drawables["ping"]->designChanged();

    if (_bridge->latency >= MAX_LATENCY)
      ((String *) _drawables["ping"])->setString("Offline");
  }

  return (true);
}

void			StatusBar::mousePressed(int x, int y)
{
  Layer::mousePressed(x, y);
  Screen::setMoving(true);
}

void			StatusBar::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
  Screen::setMoving(false);
}

void			StatusBar::settingChanged()
{
  Rect	rec = Rect(Screen::getSize().x / 2 - jag::CLIENT_WIDTH / 2,
      Screen::getSize().y / 2 + jag::CLIENT_HEIGHT / 2 - HEIGHT, jag::CLIENT_WIDTH, HEIGHT);
  _rec = rec;

  _drawables["ping"]->setRect(Rect(_rec.left + _rec.width - 80, _rec.top, 60, 20));
  _drawables["latency"]->setRect(Rect(_rec.left + _rec.width - 80, _rec.top - 26, 60, 20));
}
