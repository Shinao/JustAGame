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
    // Ackfield - Client will manage it when the sequence uptade
    AcknowledgeField			_ack_field;

    // In case of UDP with no ID
    sf::IpAddress			_ip;

    inline bool				isSequenceMoreRecent(Sequence check_sequence);
    inline AcknowledgeField		getDiff(Sequence seq);

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
    void				updateSequence(Sequence seq);
    AcknowledgeField			getAckField() const;
    void				acknowledge(Sequence seq);
};

#endif
