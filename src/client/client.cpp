#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <GL/glew.h>
#include "../ini/socket/UDPSocket.hpp"
#include "GameManager.hpp"

int main(int argc, char **argv)
{
	// UDPSocket server;
	// if (!server.init())
	// {
	// 	std::cout << "Stop !" << std::endl;
	// 	return -1;
	// }
	// Sockets::Address addr;
	// addr.set("127.0.0.1", 39959U);

	// std::string data("Salut, tu fait quoi !");
	// server.send(data.c_str(), data.size(), addr);

	// std::cout << data << std::endl;

	// system("PAUSE");
	GameManager game;

	if(argc < 2)
	{
		printf("2Usage : %s [address] [pseudo]\n", argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}