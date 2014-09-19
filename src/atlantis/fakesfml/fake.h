#ifndef FAKE_H_
#define FAKE_H_

/*
 * Implements the same methods as SFML 1.6 in order to mask it. This is used
 * to easily hook into the socket functions presented by SFML and write custom
 * linking functions, and even fake sockets.
 */

#include "Socket.h"
#include "IPAddress.h"
#include "Selector.h"
#include "SocketTCP.h"

#endif /* FAKE_H_ */
