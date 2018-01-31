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

		inline uint32_t getIp() const;
		inline uint16_t getPort() const;

		SOCKADDR_IN sin;

		std::string toString() const;
		unsigned char GetByte(int n) const;
	};

}

bool operator==(const Sockets::Address& a1, const Sockets::Address& a2);

#endif // !ADDRESS_HPP
