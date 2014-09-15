#ifndef APLAYER_HH_
# define APLAYER_HH_

# include <SFML/Graphics.hpp>
# include <string>
# include "Network/Protocol.hh"

class Client;

// APlayer used for Server and Client as an abstract class
// Implement it and for each new player create your own class inherited from it

class APlayer
{
  protected:
    std::string			_name;
    sf::Color			_color;
    ClientID			_id;
    Ping			_ping;
    bool			_is_admin;

    Client			*_client;

  public:
    APlayer();
    ~APlayer();

    const std::string		&getName() const;
    void			setName(const std::string &name);
    const sf::Color		&getColor() const;
    void			setColor(const sf::Color &color);
    void			setId(ClientID id);
    ClientID			getId() const;
    Ping			getPing() const;
    void			setPing(Ping ping);

    // Server specific
    void			setClient(Client *client);
    Client			*getClient();
};

#endif

