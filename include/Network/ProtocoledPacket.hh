#ifndef PACKET_HH_
# define PACKET_HH_

# include "Network/Network.hh"

// ProtocoledPacket inherited from SFML Packet
// Build a Header specific to the protocol (reliability)

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

  public:
    ProtocoledPacket(Client *client, Reliability rel = UDPReliable);
    ~ProtocoledPacket();

    Client			*getClient();
};

#endif
