#ifndef PACKET_HH_
# define PACKET_HH_

# include "Network.hh"

// ProtocoledPacket inherited from SFML Packet
// Build a Header specific to the protocol (reliability)
// Use generate to create a packet - deleted in the network send

class ProtocoledPacket : public sf::Packet
{
  private:
    Client			*_client;
    Network::Reliability	_reliability;
    Sequence			_sequence;
    RequestID			_request_id;

    // Ping capacity
    sf::Clock			*_clock;

    static Sequence		_sequence_counter;

  public:
    // Received packet
    ProtocoledPacket();
    // Only use this to send packet
    ProtocoledPacket(Client *client, RequestID req, Network::Reliability rel = Network::UDPReliable);
    ~ProtocoledPacket();

    void			setClient(Client *client);
    Client			*getClient();
    Sequence			getSequence() const;
    void			setSequence(Sequence seq);
    Network::Reliability	getReliability() const;
    void			setReliability(Network::Reliability rel);
    bool			isReliable() const;
    bool			hasAcknowledgment() const;
    int				getElapsedTime() const;
    RequestID			getRequestID() const;
    void			setRequestID(RequestID id);
    void			generateSequence();
};

#endif
