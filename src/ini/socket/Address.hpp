#ifndef ADDRESS_HPP
# define ADDRESS_HPP

namespace Sockets
{
	class Address
	{
	public:
		Address() = {};
		~Address() {};
		

		SOCKADDR_IN sin

	};

	bool operator==(Address const &d1, SOCKADDR_IN const &csin)
	{
		return d1.sin.sin_addr.s_addr == csin->sin_addr.s_addr
			&& d1.sin.sin_port == csin->sin_port;
	}
}


#endif // ADDRESS_HPP