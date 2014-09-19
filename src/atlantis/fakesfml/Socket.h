#ifndef SOCKET_H_
#define SOCKET_H_

namespace sf {

class Socket {
public:
	Socket();
	virtual ~Socket();

	enum Status {
		Done,         ///< The socket has sent / received the data
		NotReady,     ///< The socket is not ready to send / receive data yet
		Disconnected, ///< The TCP socket has been disconnected
		Error         ///< An unexpected error happened
	};
};

} /* namespace sf */

#endif /* SOCKET_H_ */
