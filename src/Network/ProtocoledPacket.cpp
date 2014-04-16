#include "Network/ProtocoledPacket.hh"

ProtocoledPacket::ProtocoledPacket(Client *client, Reliability rel) :
  _client(client),
  _reliability(rel)
{
}

ProtocoledPacket::~ProtocoledPacket()
{
}

Client			*ProtocoledPacket::getClient()
{
  return (_client);
}

ProtocoledPacket	*ProtocoledPacket::generate(Client *client, RequestID req, Reliability rel)
{
  ProtocoledPacket *packet = new ProtocoledPacket(client, rel);

  // Generate header
  *packet << (rel == UDPReliable ? Network::REQUEST_RELIABLE : Network::REQUEST_UNRELIABLE) << req;

  // Don't need Acknowledgement if Unconnected
  if (rel == Unconnected)
    return (packet);

  // Remote sequence for reference and ack field
  *packet << client->getSequence() << client->getAckField();



  return (packet);
}

Sequence		ProtocoledPacket::getSequence()
{
  return (_sequence);
}

void			ProtocoledPacket::setSequence(Sequence seq)
{
  _sequence = seq;
}
