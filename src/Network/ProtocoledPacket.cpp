#include "Network/ProtocoledPacket.hh"

Sequence ProtocoledPacket::_sequence_counter = 1;

ProtocoledPacket::ProtocoledPacket() :
  _client(NULL)
{
}

ProtocoledPacket::ProtocoledPacket(Client *client, RequestID req, Network::Reliability rel) :
  _client(client),
  _reliability(rel)
{
  // Generate header
  *this << (isReliable() ? Network::REQUEST_RELIABLE : Network::REQUEST_UNRELIABLE);

  // Don't need Acknowledgement if Unconnected
  if (rel == Network::Unconnected)
  {
    *this << req;
    return ;
  }

  // Only add for ack packet
  if (hasAcknowledgment())
  {
    generateSequence();
    *this << _sequence;

    // Ping capacity only on acknowlegmed packet
    _clock = new sf::Clock();
  }

  // Packet sequence + Remote sequence for reference and ack field
  *this << client->getSequence() << client->getAckField();

  // Request ID
  *this << req;
}

ProtocoledPacket::~ProtocoledPacket()
{
}

void			ProtocoledPacket::setClient(Client *client)
{
  _client = client;
}

Client			*ProtocoledPacket::getClient()
{
  return (_client);
}

Sequence		ProtocoledPacket::getSequence() const
{
  return (_sequence);
}

void			ProtocoledPacket::setSequence(Sequence seq)
{
  _sequence = seq;
}

void			ProtocoledPacket::setReliability(Network::Reliability rel)
{
  _reliability = rel;
}

Network::Reliability	ProtocoledPacket::getReliability() const
{
  return (_reliability);
}

bool			ProtocoledPacket::isReliable() const
{
  return (_reliability == Network::TCP || hasAcknowledgment());
}

bool			ProtocoledPacket::hasAcknowledgment() const
{
  return (_reliability == Network::Reliable || _reliability == Network::Variable);
}

int			ProtocoledPacket::getElapsedTime() const
{
  return (_clock->getElapsedTime().asMilliseconds());
}

RequestID		ProtocoledPacket::getRequestID() const
{
  return (_request_id);
}

void			ProtocoledPacket::setRequestID(RequestID id)
{
  _request_id = id;
}

void			ProtocoledPacket::generateSequence()
{
  _sequence = ++_sequence_counter;
}
