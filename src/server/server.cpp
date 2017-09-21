#include "../ini/socket/UDPSocket.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	UDPSocket server;

	if (!server.init())
	{
		std::cout << "Stop !" << std::endl;
		return -1;
	}
	server.bind(39959U);
	Sockets::Address addr;
	char data[255];
	int i = 0;
	std::cout << "lancer ..." << std::endl;


	while (true) {
		i = server.recv(data, 255, addr);
		data[i] = '\0';
		std::cout << data << std::endl;
	}
	
	system("PAUSE");
	return 0;
}
