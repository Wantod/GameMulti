#include "../ini/socket/UDPSocket.hpp"
#include <iostream>
#include "../ini/server.hpp"

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
	addr = server.getSocket();
	char data[255];
	int i = 0;
	std::cout << "lancer ...: " << addr.getPort() << std::endl;
	
	while (true) {
		i = server.recv(data, 250, addr);
		if (i != -1) {
			data[i] = '\0';
			std::cout << data << std::endl;
		}
	}
	system("PAUSE");
	return 0;*/
}
