#ifndef SOCKETTCP_H_
#define SOCKETTCP_H_

#include <cstdlib>

namespace sf {

class SocketTCP : protected Socket {
public:
	SocketTCP();
	virtual ~SocketTCP();

	Socket::Status Send(const char *data, std::size_t size);
	Socket::Status Receive(char *data, std::size_t max_size, std::size_t &received);
	bool Close();
	bool Listen(unsigned short port);
	Socket::Status Accept(SocketTCP &connected, IPAddress *address=NULL);
	void SetBlocking(bool blocking);
	Socket::Status Connect (unsigned short Port, const IPAddress &HostAddress, float Timeout=0.f);
};

} /* namespace sf */

#endif /* SOCKETTCP_H_ */
