#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP
#pragma once

#include "Sockets.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#define BUF_SIZE 1024

class UDPSocket
{
	public:
		UDPSocket();
		~UDPSocket();

		void send(SOCKET sock, SOCKADDR_IN *sin, const char *buffer);
		int recv(int &sender, char *data, int size);
		bool wait();
		bool bind(int port = 8080);
		bool init();

	private:
		SOCKET sock;
};

#endif // UDPSOCKET_HPP