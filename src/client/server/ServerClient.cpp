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
	while (!_end) {
		// savoir si on a reçu un message

	}
}

void ServerClient::run() {
	_serverThread = std::make_unique<std::thread>([&]() {
		_end = false;
		boucle();
	});
}

void ServerClient::stop() {
	_end = true;
}