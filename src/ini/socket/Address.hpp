#ifndef ADDRESS_HPP
# define ADDRESS_HPP

# include "Sockets.hpp"
# include <cstdint>

namespace Sockets {

	class Address
	{
	public:
		Address();
		~Address();
		
		void set(SOCKADDR_IN addr);
		bool set(const char *address, unsigned short port);

		uint32_t getIp();
		uint16_t getPort();

		SOCKADDR_IN sin;
	};

}

bool operator==(const Sockets::Address& a1, const Sockets::Address& a2);

#endif // !ADDRESS_HPP
