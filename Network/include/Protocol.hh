#ifndef PROTOCOL_HH_
# define PROTOCOL_HH_

//
// Protocol information - Request/Port/Id
//

typedef		sf::Uint16	ProtocolInfo;
typedef		sf::Uint16	AcknowledgeField;
typedef		sf::Uint16	RequestID;
typedef		sf::Uint16	Sequence;


// RequestID Network Packet
// If reserved : don't take the callback
namespace Request
{
  // [RESERVED] Keep-Alive
  const RequestID		Ping = 0;
  // Is there a server - Local
  const RequestID		Allo = 1;
  // Client connected
  const RequestID		Connexion = 2;
  // Client Disconnected
  const RequestID		Disconnexion = 3;
  // [RESERVED] Update (get info on all players)
  const RequestID		Update = 4;
  // [RESERVED] Used when a new TCP Connection is established - Need a UDP Request to get the port
  const RequestID		UDPEstablishment = 5;
  // [RESERVED] Used when the client respond to the server with UDP Request
  const RequestID		UDPEstablished = 6;
};


namespace Network
{
  enum Status
  {
    Connected,
    Disconnected,
    InProgress
  };

  enum Reliability
  {
    // Tcp
    TCP,
    // Packet will be acknowledge - Resend if necessary
    UDPReliable,
    // Reliable but drop if another request with the same ID is sended
    UDPVariable,
    // Dropped ? Don't care.
    Unreliable,
    // Not a client (Broadcast...)
    Unconnected
  };

  const ProtocolInfo	PROTOCOL_MAGIC = 0xCC1A;
  const ProtocolInfo	REQUEST_UNRELIABLE = PROTOCOL_MAGIC;
  const ProtocolInfo	REQUEST_RELIABLE = PROTOCOL_MAGIC | 0x1;

  const int		MAX_SEQUENCE = 2 ^ (sizeof(Sequence) * 8);
  const int		ACKFIELD_SIZE = sizeof(AcknowledgeField) * 8;

  const int		CLIENT_PORT = 52025;
  const int		SERVER_PORT = 25052;
};

#endif
