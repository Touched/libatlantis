#ifndef IPADDRESS_H_
#define IPADDRESS_H_

namespace sf {

class IPAddress {
public:
	IPAddress();
	virtual ~IPAddress();

	static IPAddress GetLocalAddress();

	bool IsValid() const;

	static IPAddress LocalHost;
};

} /* namespace sf */

#endif /* IPADDRESS_H_ */
