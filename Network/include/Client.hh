#ifndef CLIENT_HH_
# define CLIENT_HH_

# include "Network.hh"
# include "APlayer.hh"

class Client
{
  private:
    static const int			PING_CALCUL_NUMBER = 5;

    sf::TcpSocket			*_socket;
    ClientID				_id;
    static ClientID			_id_counter;
    Ping				_ping;
    Ping				_ping_inc;
    Ping				_ping_counter;
    bool				_is_ready;
    // Used for innactivity timer
    sf::Clock				_clock;

    // Udp port
    int					_port;

    //
    // Reliability
    //
    // Remote sequence of the host
    Sequence				_sequence;
    // Ackfield - Client will manage it when the sequence uptade
    AcknowledgeField			_ack_field;

    // In case of UDP with no ID
    sf::IpAddress			_ip;

    // Reliable packets waiting for acknowledgement
    std::map<Sequence, ProtocoledPacket *>	_waiting_packets;

    // Server specific - We want our player to be directly linked to our client
    APlayer					*_player;

  public:
    static const ClientID		NULL_ID = 0;

    Client();
    ~Client();

    sf::TcpSocket			&getSocket();
    void				setSocket(sf::TcpSocket *socket);
    ClientID				getId() const;
    void				setId(ClientID id);
    int					getPort() const;
    void				setPort(int port);
    const sf::IpAddress			getIp() const;
    void				setIp(const sf::IpAddress &ip);
    Sequence				getSequence() const;
    AcknowledgeField			getAckField() const;
    void				acknowledge(Sequence seq);
    Network::Acknowledgment		getAcknowledgment(Sequence seq) const;
    void				addPing(Ping ms);
    Ping				getPing() const;
    void				ready();
    bool				isReady() const;
    sf::Clock				&getClock();
    std::map<Sequence, ProtocoledPacket *>	&getWaitingPackets();

    APlayer				*getPlayer();
};

#endif
