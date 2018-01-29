#ifndef SERVERCLIENT_HPP
# define SERVERCLIENT_HPP

# include <iostream>
# include <atomic>

# include <thread>
# include <mutex>


class ServerClient
{
public:
	ServerClient();
	~ServerClient();

	void boucle();
	void run();
	void stop();

	std::unique_ptr<std::thread> _serverThread;
protected:
	std::atomic<bool> _end;
};



#endif // !SERVERCLIENT_HPP
