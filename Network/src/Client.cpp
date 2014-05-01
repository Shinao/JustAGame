# include "Client.hh"

ClientID	Client::_id_counter = 1;

Client::Client() :
  _socket(NULL),
  _id(++_id_counter),
  _ping(0),
  _ping_inc(0),
  _ping_counter(0),
  _is_ready(false),
  _sequence(0),
  _ack_field(0)
{
}

Client::~Client()
{
  if (_socket != NULL)
    delete _socket;
}

sf::TcpSocket			&Client::getSocket()
{
  return (*_socket);
}

ClientID			Client::getId() const
{
  return (_id);
}

int				Client::getPort() const
{
  return (_port);
}

void				Client::setPort(int port)
{
  _port = port;
}

void				Client::setId(ClientID id)
{
  _id = id;
}

const sf::IpAddress		Client::getIp() const
{
  return (_ip);
}

void				Client::setIp(const sf::IpAddress &ip)
{
  _ip = ip;
}

void				Client::setSocket(sf::TcpSocket *socket)
{
  _socket = socket;
  _ip = socket->getRemoteAddress();
}

Sequence			Client::getSequence() const
{
  return (_sequence);
}

// Acknowledge a reception of a packet by putting it into the ack field or new remote sequence
void				Client::acknowledge(Sequence seq)
{
  if (_sequence == seq)
    return ;

  if (!Network::isSequenceMoreRecent(_sequence, seq))
  {
    Sequence diff = Network::getSequenceDifference(_sequence, seq) - 1;

    // Sequence is out of bound of AckField
    if (diff > Network::ACKFIELD_SIZE)
      return ;

    std::cout << "Acknowledging their packet [" << seq << "]" << std::endl;

    _ack_field |= (0x1 << diff);

    return ;
  }

  std::cout << "New Remote Sequence [" << seq << "]" << std::endl;
    std::cout << (std::bitset<Network::ACKFIELD_SIZE>) _ack_field << " >> ";

  // Update AckField and sequence
  Sequence diff = Network::getSequenceDifference(_sequence, seq) - 1;
  _sequence = seq;
  _ack_field <<= diff;

  std::cout << (std::bitset<Network::ACKFIELD_SIZE>) _ack_field << std::endl;
}

Network::Acknowledgment		Client::getAcknowledgment(Sequence seq) const
{
  if (Network::isSequenceMoreRecent(_sequence, seq))
    return (Network::NonAcknowledged);

  Sequence	diff = Network::getSequenceDifference(_sequence, seq) - 1;

  // Search in ackfield
  if (_sequence == seq || _ack_field & (0x1 << diff))
    return (Network::Acknowledged);

  // If our packet is out of ackfield - Not acknowledged
  if (diff > Network::ACKFIELD_SIZE)
    return (Network::OutOfAckfield);

  return (Network::NonAcknowledged);
}

AcknowledgeField		Client::getAckField() const
{
  return (_ack_field);
}

void				Client::addPing(Ping ms)
{
  ++_ping_counter;
  _ping_inc += ms;

  // Update the ping if necessary
  if (_ping_counter == PING_CALCUL_NUMBER)
  {
    _ping = _ping_inc / PING_CALCUL_NUMBER;
    _ping_inc = 0;
    _ping_counter = 0;
  }
}

Ping				Client::getPing() const
{
  return (_ping);
}

std::map<Sequence, ProtocoledPacket *>	&Client::getWaitingPackets()
{
  return (_waiting_packets);
}

void				Client::ready()
{
  _is_ready = true;
}

bool				Client::isReady() const
{
  return (_is_ready);
}

sf::Clock			&Client::getClock()
{
  return (_clock);
}

Player				*Client::getPlayer()
{
  return (_player);
}
