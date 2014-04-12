# include <SFML/Network.hpp>
# include "Network/Client.hh"

// Network for server and client
// Using thread
// Call update which will use the callback for each pending request received
// A Packet must start with the RequestID
// If UDP is used, the packet must start with the client ID
// If the clientID is 0, then it will create a new client and set is IP
// this client must be deleted when the callback is called

typedef		sf::Uint16	RequestID;
typedef		std::function<void (Client *, sf::Packet &)>	CallbackRequest;

// RequestID Network Packet
namespace Request
{
  const RequestID		Ping = 0;
  const RequestID		Allo = 1;
  const RequestID		Connexion = 2;
  const RequestID		Disconnexion = 3;
};

namespace Network
{
  const int		CLIENT_PORT = 52025;
  const int		SERVER_PORT = 25052;

  enum Status
  {
    Connected,
    Disconnected,
    InProgress
  };

  bool			init(int port, int is_server);
  void			clear();
  void			update();

  sf::Socket::Status	send(sf::Packet &packet, const sf::IpAddress &ip, unsigned short port);
  sf::Socket::Status	send(sf::Packet &packet, Client *client);
  void			addRequest(RequestID id, const CallbackRequest &cb);
};
