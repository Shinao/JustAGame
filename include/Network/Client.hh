#ifndef CLIENT_HH_
# define CLIENT_HH_

# include <SFML/Network.hpp>

class Client
{
  private:
    sf::TcpSocket			_socket;

  public:
    Client();
    ~Client();

    sf::TcpSocket			&getSocket();
};

#endif
