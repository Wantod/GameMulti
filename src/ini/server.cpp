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
	Packet data2(255);
	Sockets::Address addr;
	
	while (!_end) {
		// std::cout << "eee" << std::endl;
		//int n = _server.recv(&data, 254, addr);
		int n = _server.recv(data2, addr);
		if (n != -1) {

			if (_listClient.find(addr) == _listClient.end()) {
				_listClient.emplace(addr, 10);
				std::cout << "Connection client ... " << _listClient.size() << " personne connecté" << std::endl;
			}

			std::cout << "Ip: " << addr.toString() << std::endl;
			//data[n] = '\0';
			std::cout << "Address ip: " << addr.toString() << std::endl;
			uint8_t id = data2.readInt8();
			std::cout << "Serveur ID: " << (int) id << std::endl;
			if (id == 1) {
				std::string test = data2.readString();
				std::cout << "Serveur STRING: " << test << std::endl;
			}
			std::string str("Bien reçu docteur !");
			_server.send(str.c_str(), str.size(), addr);
			data2.clear();
		}
	}
}

void Server::run() {
	_end = false;

	// init server socket
	_server.init();
	_server.bind(8912U);

	// start thread
	_serverThread = std::make_unique<std::thread>([&]() {
		// thread while
		recv_thread();
	});
}

void Server::stop() {
	_end = true;
}