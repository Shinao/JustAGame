#include "Network/ProtocoledPacket.hh"

ProtocoledPacket::ProtocoledPacket(Client *client, Reliability rel) :
  _client(client),
  _reliability(rel)
{
  // Generate header
  *this << (rel == UDPReliable ? Network::REQUEST_RELIABLE : Network::REQUEST_UNRELIABLE);

  // Don't need Acknowledgement if Unconnected
  if (rel == Unconnected)
    return ;
}

ProtocoledPacket::~ProtocoledPacket()
{
}

Client			*ProtocoledPacket::getClient()
{
  return (_client);
}
