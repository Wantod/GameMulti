#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <atomic>

# include <thread>
# include <mutex>

# include <unordered_map>
# include "socket\UDPSocket.hpp"

class Server
{
public:
	Server();
	~Server();
	
	void recv_thread();
	void run();
	void stop();

	std::unique_ptr<std::thread> _serverThread;

protected:
	std::atomic<bool> _end;
	UDPSocket _server;
	std::unordered_map<Sockets::Address, int> _listClient;
};

#endif // !SERVER_HPP