# include <SFML/Network.hpp>
# include "Network/Client.hh"

// Network for server and client
// Using thread
// Call update which will use the callback for each pending request received

namespace Network
{
  typedef		sf::Uint16	RequestID;
  typedef		std::function<void (Client *, sf::Packet &)>	Callback;

  bool			init(int port, int is_server);
  void			clear();
  void			update();
};
