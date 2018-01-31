#include "Server.hpp"

Server::Server() : _end(true), _serverThread(nullptr)
{

}

Server::~Server() {
	if (_serverThread != nullptr)
		_serverThread->join();
}

void Server::boucle()
{
	char data[255];
	Sockets::Address addr;
	
	while (!_end) {
		int n = _server.recv(&data, 254, addr);
		if (n != -1) {
			data[n] = '\0';
			std::cout << "Serveur: " << data << std::endl;
			std::string str("Bien reçu docteur !");
			_server.send(str.c_str(), str.size(), addr);
		}
	}
}

void Server::run() {
	_serverThread = std::make_unique<std::thread>([&]() {
		_end = false;

		_server.init();
		_server.bind(8912U);
		boucle();
	});
}

void Server::stop() {
	_end = true;
}