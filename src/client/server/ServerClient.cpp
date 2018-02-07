#include "ServerClient.hpp"

ServerClient::ServerClient() : _end(true), _serverThread(nullptr)
{

}

ServerClient::~ServerClient() {
	if (_serverThread != nullptr)
		_serverThread->join();
}

void ServerClient::boucle()
{
	char data[255];
	Sockets::Address addrServer;
	addrServer.set("127.0.0.1", 8912U);
	_client.send("Salut", 5, addrServer);
	_client.send("Salut2", 6, addrServer);
	_client.send("Salut3", 7, addrServer);
	Packet pk(std::string("test TESFJ ZOEHFZ EPOFHZ EPOHZFP UIZE\n\n"));
	_client.send(pk, addrServer);

	Sockets::Address addr;
	while (!_end) {
		// savoir si on a reçu un message
		int n = _client.recv(&data, 254, addr);
		if (n != -1) {
			data[n] = '\0';
			std::cout << "Client: " << data << std::endl;
		}
	}
}

void ServerClient::run() {
	_serverThread = std::make_unique<std::thread>([&]() {
		_end = false;

		_client.init();
		// _client.bind(8912U);
		boucle();
	});
}

void ServerClient::stop() {
	_end = true;
}