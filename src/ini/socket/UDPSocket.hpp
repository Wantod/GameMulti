#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP
#pragma once

#include "Sockets.hpp"

#include <iostream>
#include <string>
#include <vector>

class UDPSocket
{
	public:
		UDPSocket();
		~UDPSocket();

		void send(SOCKET sock, SOCKADDR_IN *sin, const char *buffer);
		int recv(Address &sender, void *data, int size);
		bool wait();
		bool bind();
		bool init();

	private:
		SOCKET sock;
};

#endif // UDPSOCKET_HPP