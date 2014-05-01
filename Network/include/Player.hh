#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <SFML/Graphics.hpp>
# include <string>
# include "Protocol.hh"

// Player used for Server and Client as an abstract class
// Implement it and for each new player create your own class inherited from it

class Player
{
  protected:
    std::string			_name;
    sf::Color			_color;
    ClientID			_id;
    Ping			_ping;

  public:
    Player();
    ~Player();

    const std::string		&getName() const;
    void			setName(const std::string &name);
    const sf::Color		&getColor() const;
    void			setColor(const sf::Color &color);
    void			setId(ClientID id);
    ClientID			getId() const;
    Ping			getPing() const;
    void			setPing(Ping ping);
};

#endif
