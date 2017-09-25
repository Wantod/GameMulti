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
	while (!_end) {
		std::cout << "Super salut " << std::endl;
	}
}

void Server::run() {
	_serverThread = std::make_unique<std::thread>([&]() {
		_end = false;
		boucle();
	});
}

void Server::stop() {
	_end = true;
}