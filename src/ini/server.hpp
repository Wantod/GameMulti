#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <atomic>

# include <thread>
# include <mutex>

class Server
{
public:
	Server();
	~Server();
	
	void boucle();
	void run();
	void stop();

	std::unique_ptr<std::thread> _serverThread;
protected:
	std::atomic<bool> _end;
};

#endif // !SERVER_HPP