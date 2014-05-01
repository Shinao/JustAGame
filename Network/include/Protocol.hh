#ifndef PROTOCOL_HH_
# define PROTOCOL_HH_

//
// Protocol information - Request/Port/Id
//

typedef		sf::Uint16	ProtocolInfo;
typedef		sf::Uint32	AcknowledgeField;
typedef		sf::Uint16	RequestID;
typedef		sf::Uint16	Sequence;


// RequestID Network Packet
// If reserved : don't take the callback
namespace Request
{
  // [RESERVED] Keep-Alive
  const RequestID		Ping = 0;
  // [RESERVED] Is there a server - Local
  const RequestID		Allo = 1;
  // Client connected - Player joined
  const RequestID		Connexion = 2;
  // Client Disconnected - Player left
  const RequestID		Disconnexion = 3;
  // [RESERVED] Update (get info on all players)
  const RequestID		Update = 4;
  // [RESERVED] Used when a new TCP Connection is established - Need a UDP Request to get the port
  const RequestID		UDPEstablishment = 5;
  // [RESERVED] Used when the client respond to the server with UDP Request
  const RequestID		UDPEstablished = 6;
  // [RESERVED] Test case
  const RequestID		Test = 7;
  // [RESERVED] Client sent his name
  const RequestID		Name = 8;
}


namespace Network
{
  enum Status
  {
    Connected,
    Disconnected,
    InProgress
  };

  enum Acknowledgment
  {
    Acknowledged,
    NonAcknowledged,
    OutOfAckfield
  };

  enum Reliability
  {
    // Tcp - slow, ordered and reliable (Message, files...)
    TCP,
    // UDP - Fast but unordered Packet will be acknowledge - Resend if necessary
    Reliable,
    // Reliable but drop if another request variable with the same RequestID is sended
    Variable,
    // UDP - Dropped ? Don't care.
    Unreliable,
    // [RESERVED] UDP - Not a client - Initialization and broadcast
    Unconnected
  };

  const ProtocolInfo	PROTOCOL_MAGIC = 0xCC1A;
  const ProtocolInfo	REQUEST_UNRELIABLE = PROTOCOL_MAGIC;
  const ProtocolInfo	REQUEST_RELIABLE = PROTOCOL_MAGIC | 0x1;

  const int		MAX_SEQUENCE = 2 ^ (sizeof(Sequence) * 8);
  const int		ACKFIELD_SIZE = sizeof(AcknowledgeField) * 8;

  const int		CLIENT_PORT = 52025;
  const int		SERVER_PORT = 25052;
}

#endif
