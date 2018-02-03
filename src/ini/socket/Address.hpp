#ifndef ADDRESS_HPP
# define ADDRESS_HPP

# include "Sockets.hpp"
# include <cstdint>

namespace Sockets {


	class Address
	{
	public:
		Address();
		Address(const Address &a);
		~Address();

		bool operator==(const Address& a2) const;
		
		void set(SOCKADDR_IN addr);
		bool set(const char *address, unsigned short port);

		inline uint32_t getIp() const;
		inline uint16_t getPort() const;

		SOCKADDR_IN sin;

		std::string toString() const;
		unsigned char GetByte(int n) const;
	};
}

/* inline bool operator==(const Sockets::Address& a1, const Sockets::Address& a2); */

namespace std {

	template <>
	struct hash<Sockets::Address>
	{
		std::size_t operator()(const Sockets::Address& k) const
		{
			return std::hash<unsigned long>()(k.sin.sin_addr.s_addr) ^ std::hash<unsigned short>()(k.sin.sin_port);
		}
	};

}

#endif // !ADDRESS_HPP
