#ifndef CLIENT_HH_
# define CLIENT_HH_

# include "Network/Network.hh"

typedef		sf::Uint16	ClientID;

class Client
{
  private:
    sf::TcpSocket			*_socket;
    ClientID				_id;

    //
    // Reliability
    //
    // Remote sequence of the host
    Sequence				_sequence;
    // Reliable packets waiting for acknowledgement
    // std::vector<ProtocoledPacket *>	_reliable_packets;

    // In case of UDP with no ID
    sf::IpAddress			_ip;

  public:
    Client();
    ~Client();

    sf::TcpSocket			&getSocket();
    void				setSocket(sf::TcpSocket *socket);
    ClientID				getId() const;
    void				setId(ClientID id);
    const sf::IpAddress			getIp() const;
    void				setIp(const sf::IpAddress &ip);
    Sequence				getSequence() const;
    void				setSequence(Sequence seq);
};

#endif
