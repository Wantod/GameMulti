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

	inline uint32_t Address::getIp() const {
		return ntohl(sin.sin_addr.s_addr);
	}

	inline uint16_t Address::getPort() const {
		return ntohs(sin.sin_port);
	}

	std::string Address::toString() const {
		std::stringstream ss;
		uint32_t ip = ntohl(sin.sin_addr.s_addr);
		ss << ((ip >> 24) & 0xFF) << '.' << ((ip >> 16) & 0xFF) << '.' << ((ip >> 8) & 0xFF) << '.' << (ip & 0xFF) << ':' << this->getPort();
		return ss.str();
	}

	unsigned char Address::GetByte(int n) const {
		uint32_t ip = this->getIp();
		return ((unsigned char*)&ip)[3 - n];
	}

}

bool operator==(const Sockets::Address& a1, const Sockets::Address& a2)
{
	if (a1.sin.sin_addr.s_addr == a2.sin.sin_addr.s_addr
		&& a1.sin.sin_port == a1.sin.sin_port)
		return true;
	return false;
}