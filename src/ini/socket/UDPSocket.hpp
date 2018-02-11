#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP
#pragma once

#include "Sockets.hpp"
#include "Packet.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

class UDPSocket
{
	public:
		UDPSocket();
		~UDPSocket();

		int recv(void *data, std::size_t size, Sockets::Address &addr);
		bool send(const void *data, std::size_t size, Sockets::Address &addr);

		int recv(Packet &p, Sockets::Address &addr);
		bool send(const Packet &ee, Sockets::Address &addr);

		bool wait();
		bool bind(unsigned short port = 8080);
		bool init(bool blocking = false);

		Sockets::Address getSocket();
	private:
		SOCKET sock;
		SOCKADDR_IN server;
};

#endif // UDPSOCKET_HPP