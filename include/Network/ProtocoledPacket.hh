#ifndef PACKET_HH_
# define PACKET_HH_

# include "Network/Network.hh"

// ProtocoledPacket inherited from SFML Packet
// Build a Header specific to the protocol (reliability)
// Use generate to create a packet - deleted in the network send

class ProtocoledPacket : public sf::Packet
{
  public:
    enum Reliability
    {
      // Tcp
      TCPReliable,
      // Packet will be acknowledge - Resend if necessary
      UDPReliable,
      // Dropped ? Don't care.
      Unreliable,
      // Not a client (Broadcast...)
      Unconnected
    };

  private:
    Client			*_client;
    Reliability			_reliability;
    ProtocoledPacket(Client *client, Reliability rel = UDPReliable);
    Sequence			_sequence;

  public:
    ~ProtocoledPacket();

    static ProtocoledPacket	*generate(Client *client, RequestID req, Reliability rel = UDPReliable);

    Client			*getClient();
    Sequence			getSequence();
    void			setSequence(Sequence seq);
};

#endif
