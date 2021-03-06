#ifndef PROTOCOL_HH_
# define PROTOCOL_HH_

//
// Protocol information - Request/Port/Id
//

typedef		sf::Uint16	Ping;
typedef		sf::Uint16	ClientID;
typedef		sf::Uint16	ProtocolInfo;
typedef		sf::Uint32	AcknowledgeField;
typedef		sf::Uint16	RequestID;
typedef		sf::Uint16	Sequence;
typedef 	sf::Uint8	Message;
typedef 	sf::Uint8	Version;




// RequestID Network Packet
// [RESERVED] : Don't take the callback
namespace Request
{
  // [RESERVED] Keep-Alive : server <-> client
  const RequestID		Ping = 0;
  // [RESERVED] Is there a server - Local : server <-> client
  const RequestID		Allo = 1;
  // [RESERVED] Client connected : server <-> client
  const RequestID		Connexion = 2;
  // [RESERVED] Client Disconnected : server <-> client
  const RequestID		Disconnexion = 3;
  // [RESERVED] Update (get info on all players) server -> client
  const RequestID		Update = 4;
  // [RESERVED] Used when a new TCP Connection is established - Need a UDP Request to get the port : server -> client
  const RequestID		UDPEstablishment = 5;
  // [RESERVED] IDPEstablished : client -> server
  const RequestID		UDPEstablished = 6;
  // [RESERVED] Test case
  const RequestID		Test = 7;
  // [RESERVED] Player sent his information (Name, color...) : client -> server
  const RequestID		PlayerInfo = 8;
  // [RESERVED] Server sent his information (Version, mode...) : server -> client
  const RequestID		ServerInfo = 9;
  // [RESERVED] Player joined the game : server -> client
  const RequestID		PlayerJoined = 10;
  // [RESERVED] Player left the game : server -> client
  const RequestID		PlayerLeft = 11;
  // [RESERVED] When a player join a server, he should receive all the data before beginning : server -> client
  const RequestID		InitGame = 12;
  // [RESERVED] When a client does not have the game - ask for download : client <-> server
  const RequestID		GetGame = 13;
  // [RESERVED] When a player send/receive a message : server <-> client
  const RequestID		Message = 14;
  // Game start : server -> client
  const RequestID		GameStart = 15;
  // Party end and client won : server -> client
  const RequestID		PlayerWon = 16;
  // Party end and client lost : server -> client
  const RequestID		PlayerLost = 17;
}

namespace MessageType
{
  const Message			Player = 1;
  const Message			Console = 2;
  const Message			Info = 3;
  const Message			Warning = 4;
  const Message			Error = 5;
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

  const int		SERVER_PORT = 25052;
  // Can be different to have multiple client on same computer
  const int		CLIENT_PORT = 52025;

  // Some utility client/server
  enum			Path
  {
    BuildDir,
    RsrcDir
  };

  const std::string	GAMES_PATH = "Games/";
  const std::string	RSRC_PATH = "rsrc/";
  const std::string	BUILD_PATH = "build/";
  const std::string	SUFFIX_SERVER = "_server";
  const std::string	SUFFIX_CLIENT = "_client";
  const std::string	SUFFIX_LIB_WIN32 = ".dll";
  const std::string	SUFFIX_LIB_UNIX = ".so";
}

#endif
