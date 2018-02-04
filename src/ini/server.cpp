#include "Server.hpp"

Server::Server() : _end(true), _serverThread(nullptr), _listClient()
{

}

Server::~Server() {
	if (_serverThread != nullptr)
		_serverThread->join();
}

void Server::recv_thread()
{
	char data[255];
	Sockets::Address addr;
	
	while (!_end) {
		// std::cout << "eee" << std::endl;
		int n = _server.recv(&data, 254, addr);
		if (n != -1) {

			if (_listClient.find(addr) == _listClient.end()) {
				_listClient.emplace(addr, 10);
				std::cout << "Connection client ... " << _listClient.size() << " personne connecté" << std::endl;
			}

			data[n] = '\0';
			std::cout << "Address ip: " << addr.toString() << std::endl;
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
		recv_thread();
	});
}

void Server::stop() {
	_end = true;
}