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

// Network for server and client
// Using thread
// Call update which will use the callback for each pending request received
// A Packet must start with a Header - See ProtocoledPacket

// If UDP is used in unconnected mode, then it will create a new client and set is IP
// This client must be deleted when the callback is called

typedef		std::function<void (ProtocoledPacket &)>	CallbackRequest;

namespace Network
{
  // Properties
  const int		KEEPALIVE_INTERVAL = 500;

  bool			init(int port, int is_server);
  void			clear();
  void			update();

  void			send(ProtocoledPacket *packet, const sf::IpAddress &ip, unsigned short port);
  void			send(ProtocoledPacket *packet);
  void			addRequest(RequestID id, const CallbackRequest &cb);

  AcknowledgeField	getSequenceDifference(Sequence seq1, Sequence seq2);
  bool			isSequenceMoreRecent(Sequence sequence, Sequence check_sequence);
};

#endif
