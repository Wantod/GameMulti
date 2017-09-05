#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP
#pragma once

#include "Sockets.hpp"

#include <string>
#include <vector>

class UDPSocket
{
	public:
		UDPSocket();
		~UDPSocket();

	private:
		SOCKET mSocket;
};

#endif // UDPSOCKET_HPP