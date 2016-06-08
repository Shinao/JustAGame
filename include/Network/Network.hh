#ifndef NETWORK_HH_
# define NETWORK_HH_

// Fucking Headers
class Client;
class ProtocoledPacket;

# include <SFML/Network.hpp>
# include "Network/Protocol.hh"
# include "Network/Client.hh"
# include "Network/ProtocoledPacket.hh"
# include <functional>
# include <iostream>
# include <bitset>

// Network for server and client
// Using thread
// Call update which will use the callback for each pending request received
// A Packet must start with a Header - See ProtocoledPacket

// connect function is threaded - will call the callback Connexion/Disconnexion
// The parameter client only need his Ip and Port set

// If UDP is used in unconnected mode, then it will create a new client and set his Ip and Port
// This client will be automatically deleted after the callback

typedef		std::function<void (ProtocoledPacket &)>	CallbackRequest;

namespace Network
{
  // Properties
  const int		UPDATE_INTERVAL = 500;
  const int		TIMEOUT = 5000;

  bool			init(int port, int is_server);
  void			clear();
  void			update();

  void			send(ProtocoledPacket *packet, const sf::IpAddress &ip, unsigned short port);
  sf::Socket::Status	send(ProtocoledPacket *packet);
  void			sendToClients(RequestID request, Network::Reliability rel, const sf::Packet &packet);
  void			addRequest(RequestID id, const CallbackRequest &cb);
  void			removeRequest(RequestID id);
  sf::Thread		*connect(Client *client);
  void			disconnect(Client *client, bool from_network = true, bool later = true);

  Sequence		getSequenceDifference(Sequence seq1, Sequence seq2);
  bool			isSequenceMoreRecent(Sequence sequence, Sequence check_sequence);
  std::string		&getPath(Path path, const std::string &game_mode = "");

  // Client sided
  void			askForServer(const CallbackRequest &cb);
  // Server sided
  void			getClientAsking(const CallbackRequest &cb);
  std::vector<Client *>	&getClients();
}

#endif
