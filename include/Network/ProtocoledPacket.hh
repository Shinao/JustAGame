#ifndef PACKET_HH_
# define PACKET_HH_

# include "Network/Network.hh"

// ProtocoledPacket inherited from SFML Packet
// Build a Header specific to the protocol (reliability)
// Use generate to create a packet - deleted in the network send

class ProtocoledPacket : public sf::Packet
{
  private:
    Client			*_client;
    Network::Reliability	_reliability;
    ProtocoledPacket(Client *client, Network::Reliability rel);
    Sequence			_sequence;

    static Sequence		_sequence_counter;

  public:
    ~ProtocoledPacket();

    static ProtocoledPacket	*generate(Client *client, RequestID req, Network::Reliability rel = Network::UDPReliable);

    Client			*getClient();
    Sequence			getSequence() const;
    void			setSequence(Sequence seq);
    Network::Reliability	getReliability() const;
    bool			isReliable() const;
};

#endif
