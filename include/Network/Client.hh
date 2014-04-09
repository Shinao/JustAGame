#ifndef CLIENT_HH_
# define CLIENT_HH_

# include <SFML/Network.hpp>

typedef		sf::Uint16	ClientID;

class Client
{
  private:
    sf::TcpSocket			_socket;
    ClientID				_id;

    // In case of UDP with no ID
    sf::IpAddress			_ip;

  public:
    Client();
    ~Client();

    sf::TcpSocket			&getSocket();
    ClientID				getId() const;
    void				setId(ClientID id);
    const sf::IpAddress			getIp() const;
    void				setIp(const sf::IpAddress &ip);
};

#endif
