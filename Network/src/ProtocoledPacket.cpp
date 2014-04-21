#include "ProtocoledPacket.hh"

Sequence ProtocoledPacket::_sequence_counter = 0;

ProtocoledPacket::ProtocoledPacket(Client *client, Network::Reliability rel) :
  _client(client),
  _reliability(rel),
  _sequence(++_sequence_counter)
{
  std::cout << "Creating packet [" << _sequence << "]" << std::endl;
}

ProtocoledPacket::~ProtocoledPacket()
{
}

Client			*ProtocoledPacket::getClient()
{
  return (_client);
}

ProtocoledPacket	*ProtocoledPacket::generate(Client *client, RequestID req, Network::Reliability rel)
{
  ProtocoledPacket *packet = new ProtocoledPacket(client, rel);

  // Generate header
  *packet << (rel == Network::UDPReliable ? Network::REQUEST_RELIABLE : Network::REQUEST_UNRELIABLE);

  // Don't need Acknowledgement if Unconnected
  if (rel == Network::Unconnected)
    return (packet);

  // Remote sequence for reference and ack field
  *packet << client->getSequence() << client->getAckField();

  // Request ID
  *packet << req;

  return (packet);
}

Sequence		ProtocoledPacket::getSequence() const
{
  return (_sequence);
}

void			ProtocoledPacket::setSequence(Sequence seq)
{
  _sequence = seq;
}

Network::Reliability	ProtocoledPacket::getReliability() const
{
  return (_reliability);
}

bool			ProtocoledPacket::isReliable() const
{
  return (_reliability == Network::TCPReliable || _reliability == Network::UDPReliable);
}
