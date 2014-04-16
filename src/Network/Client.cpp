# include "Network/Client.hh"

ClientID	Client::_id_counter = 0;

Client::Client() :
  _socket(NULL),
  _id(_id_counter++),
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

void				Client::updateSequence(Sequence seq)
{
  if (!Network::isSequenceMoreRecent(_sequence, seq))
  {
    acknowledge(seq);
    return ;
  }

  // Update AckField and sequence
  Sequence diff = Network::getSequenceDifference(_sequence, seq);
  _sequence = seq;
  _ack_field >>= diff;

  // Add old sequence
  _ack_field |= (0x1 << (Network::ACKFIELD_SIZE - diff));
}

// Acknowledge a reception of a packet by putting it into the ack field
void				Client::acknowledge(Sequence seq)
{
  Sequence diff = Network::getSequenceDifference(_sequence, seq);

  // Sequence is out of bound of AckField
  if (diff > Network::ACKFIELD_SIZE)
    return ;

  _ack_field |= (0x1 << (Network::ACKFIELD_SIZE - diff));

  std::cout << "Acknowledging their packeet [" << seq << "]" << std::endl;
}

AcknowledgeField		Client::getAckField() const
{
  return (_ack_field);
}
