# include "Network/Client.hh"

Client::Client() :
  _socket(NULL),
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
}

Sequence			Client::getSequence() const
{
  return (_sequence);
}

void				Client::updateSequence(Sequence seq)
{
  if (!isSequenceMoreRecent(seq))
    return ;

  // Update AckField and sequence
  Sequence diff = (_sequence - seq) * -1;
  _sequence = seq;
  _ack_field >>= diff;
}

// Acknowledge a reception of a packet by putting it into the ack field
void				Client::acknowledge(Sequence seq)
{
  Sequence diff = getDiff(seq);

  // Sequence is out of bound of AckField
  if (diff > ACFIELD_SIZE)
    return ;

  _ack_field |= (0x1 << (ACFIELD_SIZE - diff));
}

inline AcknowledgeField		Client::getDiff(Sequence seq)
{
  Sequence our_sequence = _sequence;

  // Looped
  if (seq - our_sequence > MAX_SEQUENCE / 2)
  {
    seq = 0;
    our_sequence += MAX_SEQUENCE - seq;
  }

  return ((our_sequence - seq) * -1);
}

inline bool			Client::isSequenceMoreRecent(Sequence check_sequence)
{
  return ((check_sequence > _sequence) && (check_sequence - _sequence <= Network::MAX_SEQUENCE / 2)) ||
    ((_sequence > check_sequence) && (_sequence - check_sequence > Network::MAX_SEQUENCE / 2));
}

AcknowledgeField		Client::getAckField() const
{
  return (_ack_field);
}
