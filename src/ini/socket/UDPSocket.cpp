#include "UDPSocket.hpp"

UDPSocket::UDPSocket() {

}

UDPSocket::~UDPSocket() {
	Sockets::CloseSocket(sock);
	Sockets::Release();
}

bool UDPSocket::init() {
	if (!Sockets::Start()) 
	{
		std::cout << "Erreur initialisation WinSock : " << Sockets::GetError();
		return false;
	}

	// init socket
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // ipv4, UDP
	if (sock == INVALID_SOCKET)
	{
		std::cout << "Erreur initialisation socket : " << Sockets::GetError();
		return false;
	}

	if (!Sockets::SetNonBlocking(sock))
	{
		std::cout << "Erreur settings non bloquant : " << Sockets::GetError();
		return false;
	}

	return true;
}

Sockets::Address UDPSocket::getSocket() {
	Sockets::Address addr;
	addr.set(server);
	return addr;
}

bool UDPSocket::bind(unsigned short port) {
	server.sin_addr.s_addr = INADDR_ANY;  // indique que toutes les sources seront acceptées
										  // UTILE: si le port est 0 il est assigné automatiquement
	server.sin_port = htons(port); // toujours penser à traduire le port en réseau
	server.sin_family = AF_INET; // notre socket est UDP
	socklen_t size = sizeof(server);

	getsockname(sock, (struct sockaddr *) &server, &size);
	
	if (::bind(sock, reinterpret_cast<SOCKADDR *>(&server), sizeof(server)) == SOCKET_ERROR)
	{
		std::cout << "Erreur bind : " << Sockets::GetError();
		return false;
	}

	return true;
}

bool UDPSocket::wait() {
	fd_set readset;
	timeval timeout = { 0 };
	int selectRedy;

	FD_ZERO(&readset);

	FD_SET(sock, &readset);
	selectRedy = select(sock + 1, &readset, nullptr, nullptr, &timeout);
	if (selectRedy == -1)
	{
		std::cout << "Erreur select : " << Sockets::GetError() << std::endl;
		return false;
	}
	else if (selectRedy > 0)
	{
		if (FD_ISSET(sock, &readset))
		{
			return true;
		}
	}

	return false;
}

int UDPSocket::recv(void *data, std::size_t size, Sockets::Address &addr)
{
	//if (!wait())
	//	return -1;

	/* a client is talking */
	int sinsize = sizeof (addr.sin);

	int n = recvfrom(sock, static_cast<char*>(data), static_cast<int>(size), 0, reinterpret_cast<sockaddr*>(&addr.sin), &sinsize);
	if (n < 0)
		return -1;
	return n;
}

bool UDPSocket::send(const void *data, std::size_t size, Sockets::Address &addr)
{

	if (sendto(sock, static_cast<const char*>(data), static_cast<int>(size), 0, reinterpret_cast<sockaddr*>(&addr.sin), sizeof (addr.sin)) < 0)
	{
		std::cout << "Erreur send()" << std::endl;
		return false;
	}

	return true;
}
