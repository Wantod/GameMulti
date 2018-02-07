#include "Address.hpp"
#include <sstream> 

namespace Sockets {
	Address::Address()
	{
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(0);
	}

	Address::Address(const Address &a)
	{
		sin = a.sin;
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
		ss << (int)this->GetByte(0) << '.' << (int)GetByte(1) << '.' << (int)GetByte(2) << '.' << (int)GetByte(3) << ':' << (int)this->getPort();
		return ss.str();
	}

	unsigned char Address::GetByte(int n) const {
		unsigned int ip = this->getIp();
		return ((unsigned char*)&ip)[3 - n];
	}

	bool Address::operator==(const Sockets::Address& a2) const
	{
		if (sin.sin_addr.s_addr == a2.sin.sin_addr.s_addr
			&& sin.sin_port == a2.sin.sin_port)
			return true;
		return false;
	}
}
/*
bool operator==(const Sockets::Address& a1, const Sockets::Address& a2)
{
	if (a1.sin.sin_addr.s_addr == a2.sin.sin_addr.s_addr
		&& a1.sin.sin_port == a2.sin.sin_port)
		return true;
	return false;
}
*/