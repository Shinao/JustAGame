#include <SFML/Network.hpp>

#include <iostream>

int	main()
{
  sf::TcpSocket	ping;

  sf::Clock	timer;
  long		latency;
  char		rsp[4096];
  size_t	len;

  ping.setBlocking(true);
  while (1)
  {
    // Getting i packet before having the latency
    latency = 0;
    for (int i = 0; i < 10; ++i)
    {
      timer.restart();

      if (ping.connect("google.com", 80, sf::seconds(2)) == sf::Socket::Done)
      {
	// Get HEAD - fastest command
	ping.send("HEAD\n\r", 6);

	if (ping.receive(rsp, 4096, len) == sf::Socket::Done)
	  latency += timer.getElapsedTime().asMilliseconds();
	else
	  latency += 2000;
      }
      else
	latency += 2000;

      ping.disconnect();
    }

    std::cout << "Latency: [" << (latency / 10) << "]" << std::endl;
    sf::sleep(sf::seconds(1));
  }

  return (0);
}

int	main2()
{
  sf::Http	ping;
  ping.setHost("http://google.com");

  sf::Http::Request	query;

  sf::Clock	timer;
  long		latency;
  sf::Http::Response	rsp;

  while (1)
  {
    // Getting 10 packet before having the latency
    latency = 0;
    for (int i = 0; i < 4; ++i)
    {
      timer.restart();

      rsp = ping.sendRequest(query);
      if (rsp.getStatus() != sf::Http::Response::ConnectionFailed)
	latency += timer.getElapsedTime().asMilliseconds();
      else
	latency += 1000;
    }

    std::cout << "Latency: [" << latency / 4 << "]" << std::endl;
    sf::sleep(sf::seconds(1));
  }

  return (0);
}
