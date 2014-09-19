#include "SocketTCP.h"

namespace sf {

SocketTCP::SocketTCP() {
	// TODO Auto-generated constructor stub

}

SocketTCP::~SocketTCP() {
	// TODO Auto-generated destructor stub
}

Socket::Status SocketTCP::Send(const char* data, std::size_t size) {
}

Socket::Status SocketTCP::Receive(char* data, std::size_t max_size,
		std::size_t& received) {
}

bool SocketTCP::Close() {
}

bool SocketTCP::Listen(unsigned short port) {
}

Socket::Status SocketTCP::Accept(SocketTCP& connected, IPAddress* address) {
}

void SocketTCP::SetBlocking(bool blocking) {
}

Socket::Status SocketTCP::Connect(unsigned short Port,
		const IPAddress& HostAddress, float Timeout) {
}

} /* namespace sf */
