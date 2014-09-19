#pragma once

#define FAKE_SFML // TODO: Remove this line

#ifdef FAKE_SFML
#include <fakesfml/fake.h>
#else
#include <SFML/Network.hpp>
#endif

#include "../common/Types.h"

class GBASockClient : public sf::SocketTCP
{
public:
	GBASockClient(sf::IPAddress server_addr);
	~GBASockClient();

	void Send(std::vector<char> data);
	char ReceiveCmd(char* data_in);

private:
	sf::IPAddress server_addr;
	sf::SocketTCP client;
};
