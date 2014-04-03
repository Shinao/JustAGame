#include "StatusBar.hh"
#include "GUI/Screen.hh"
#include "GUI/String.hh"


void	*latency(void *);

StatusBar::StatusBar() :
  Layer::Layer(),
  _latency(-1)
{
  Rect	rec = Rect(0, Screen::getSize().y - HEIGHT, Screen::getSize().x, HEIGHT);
  _rec = rec;

  _good = sf::Color(63, 146, 210);
  _okay = sf::Color(255, 154, 2);
  _bad = sf::Color(200, 100, 100);

  String	*text = new String("Loading", jag::getTheme("Ping"));
  text->setBorder(Border::Top);
  text->setAlignment(Item::Alignment::Center);
  text->setTooltip("Latency from google");
  text->setRect(Rect(_rec.width - 80, _rec.top, 60, 20));

  add(text, "ping");

  _bridge = new BridgeThread;
  _bridge->running = true;
  _bridge->latency = -1;
  pthread_create(&_thread, NULL, &latency, _bridge);
}

StatusBar::~StatusBar()
{
  _bridge->running = false;
}

void			*latency(void *arg)
{
  const int		NUMBER_CYCLE = 10;
  sf::TcpSocket		pinger;
  sf::Clock		timer;
  long			latency;
  BridgeThread		*bridge = (BridgeThread *) arg;
  char			rsp[4096];
  size_t		len;

  pinger.setBlocking(true);
  while (bridge->running)
  {
    // Getting i packet before having the latency
    latency = 0;
    for (int i = 0; i < NUMBER_CYCLE; ++i)
    {
      timer.restart();

      if (pinger.connect("google.com", 80, sf::seconds(2)) == sf::Socket::Done)
      {
	// Get HEAD - fastest command
	pinger.send("HEAD\n\r", 6);

	if (pinger.receive(rsp, 4096, len) == sf::Socket::Done)
	  latency += timer.getElapsedTime().asMilliseconds();
	else
	  latency += 2000;
      }
      else
	latency += 2000;

      pinger.disconnect();
    }

    bridge->latency = latency / NUMBER_CYCLE;
    sf::sleep(sf::seconds(1));
  }

  delete bridge;
  return (NULL);
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
  }

  return (true);
}
