#ifndef STATUS_BAR_HH_
# define STATUS_BAR_HH_

# include <pthread.h>
# include <sstream>
# include <SFML/Graphics.hpp>
# include <SFML/Network.hpp>
# include "Layer.hh"
# include "Menu.hh"

// Display ping

struct		BridgeThread
{
  long		latency;
  bool		running;
};


class StatusBar : public Layer
{
  public:
    static const int		HEIGHT = 32;

    sf::Color			_good;
    sf::Color			_okay;
    sf::Color			_bad;
    long			_latency;
    BridgeThread		*_bridge;
    pthread_t			_thread;

  private:

  public:
    StatusBar();
    ~StatusBar();

    void			mousePressed(int x, int y);
    void			mouseReleased(int x, int y);
    bool			update(sf::RenderWindow &win);
};

#endif

