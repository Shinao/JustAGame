#ifndef PSMANAGER_HH_
# define PSMANAGER_HH_

# include "Thor/Particles.hpp"
# include <list>
# include <SFML\Graphics.hpp>
# include <SFML\System.hpp>
# include <SFML\Window.hpp>

class PSManager
{
  public:
    struct PSInfo
    {
      thor::ParticleSystem	*system;
      int			draw_priority = 0;
      sf::Time			duration;
    };

  private:
    std::list<PSInfo *>		_pss;
    sf::Clock			_ps_clock;
    sf::Vector2f		_adjustment;

  public:
    PSManager();
    ~PSManager();

    void			add(PSInfo *info);
    void			draw(sf::RenderWindow &window);
    void			cameraMoved(sf::Vector2f &adjustment);
    void			clear();
};

#endif
