#ifndef SERVERCLIENT_HPP
# define SERVERCLIENT_HPP

# include <iostream>
# include <atomic>

# include <thread>
# include <mutex>

# include "../../ini/socket\UDPSocket.hpp"

class ServerClient
{
public:
	ServerClient();
	~ServerClient();

	void boucle();
	void run();
	void stop();

	// recuperation des message a parser
	// connection d'un joueur
	// deconnection
	// deplacement
	// message
	// bloc modification

	std::unique_ptr<std::thread> _serverThread;

protected:
	UDPSocket _client;
	std::mutex _mutexMsg;
	std::atomic<bool> _end;
};



#endif // !SERVERCLIENT_HPP
