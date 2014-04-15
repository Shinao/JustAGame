#ifndef NETWORK_HH_
# define NETWORK_HH_

# include <SFML/Network.hpp>
# include "Network/Protocol.hh"
# include "Network/ProtocoledPacket.hh"
# include "Network/Client.hh"

// Network for server and client
// Using thread
// Call update which will use the callback for each pending request received
// A Packet must start with the RequestID
// If UDP is used, the packet must start with the client ID
// If the clientID is 0, then it will create a new client and set is IP
// this client must be deleted when the callback is called

typedef		std::function<void (Client *, sf::Packet &)>	CallbackRequest;

namespace Network
{
  enum Status
  {
    Connected,
    Disconnected,
    InProgress
  };

  bool			init(int port, int is_server);
  void			clear();
  void			update();

  void			send(ProtocoledPacket &packet, const sf::IpAddress &ip, unsigned short port);
  void			send(ProtocoledPacket &packet);
  void			addRequest(RequestID id, const CallbackRequest &cb);
};

#endif
