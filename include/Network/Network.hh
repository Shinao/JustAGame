# include <SFML/Network.hpp>
# include "Network/Client.hh"

// Network for server and client
// Using thread
// Call update which will use the callback for each pending request received

typedef		sf::Uint16	RequestID;
typedef		std::function<void (Client *, sf::Packet &)>	CallbackNet;

namespace Network
{

  bool			init(int port, int is_server);
  void			clear();
  void			update();

  void			send(sf::Packet &packet, sf::IpAddress &ip);
  void			send(sf::Packet &packet, Client *client);
  void			addRequest(RequestID id, const CallbackNet &cb);
};
