#include "Address.hpp"

namespace Sockets {
	Address::Address()
	{
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(0);
	}

	Address::~Address()
	{
	}

	void Address::set(SOCKADDR_IN addr) {
		sin = addr;
	}

	bool Address::set(const char *address, unsigned short port) {
		struct hostent *hostinfo;
		hostinfo = gethostbyname(address);
		if (hostinfo == NULL)
		{
			std::cerr << "Unknown host " << address << "." << std::endl;
			return false;
		}

		sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
		sin.sin_port = htons(port);
		sin.sin_family = AF_INET;
		return true;
	}

	uint32_t Address::getIp() {
		return ntohl(sin.sin_addr.s_addr);
	}

	uint16_t Address::getPort() {
		return ntohs(sin.sin_port);
	}
}

bool operator==(const Sockets::Address& a1, const Sockets::Address& a2)
{
	if (a1.sin.sin_addr.s_addr == a2.sin.sin_addr.s_addr
		&& a1.sin.sin_port == a1.sin.sin_port)
		return true;
	return false;
}