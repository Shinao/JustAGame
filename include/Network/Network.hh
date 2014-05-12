#ifndef NETWORK_HH_
# define NETWORK_HH_

// Fucking Headers
class Client;
class ProtocoledPacket;

# include <SFML/Network.hpp>
# include "Protocol.hh"
# include "Client.hh"
# include "ProtocoledPacket.hh"
# include <iostream>
# include <bitset>

// Network for server and client
// Using thread
// Call update which will use the callback for each pending request received
// A Packet must start with a Header - See ProtocoledPacket

// connect function is threaded - will call the callback passed as parameter
// The parameter client only need his Ip and Port set
// connect should not be called inside a CallbackRequest function to avoid deadlock

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
  sf::Thread		*connect(Client *client);

  Sequence		getSequenceDifference(Sequence seq1, Sequence seq2);
  bool			isSequenceMoreRecent(Sequence sequence, Sequence check_sequence);

  // Client sided
  void			askForServer(const CallbackRequest &cb);
  // Server sided
  void			getClientAsking(const CallbackRequest &cb);
  std::vector<Client *>	&getClients();
}

#endif
