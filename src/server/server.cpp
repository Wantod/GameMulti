#include "../ini/socket/Sockets.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <thread>

#define PORT	 	1977
#define MAX_CLIENTS 	100
#define BUF_SIZE	1024

typedef struct
{
	SOCKADDR_IN sin;
	char name[BUF_SIZE];
} Client;

// std ::vector<Client> clients ;

#include <iostream>

static int read_client(SOCKET sock, SOCKADDR_IN *csin, char *buffer);
static void write_client(SOCKET sock, SOCKADDR_IN *csin, const char *buffer);
static void send_message_to_all_clients(int sock, Client *clients, Client *client, int actual, const char *buffer, char from_server);
static int check_if_client_exists(Client *clients, SOCKADDR_IN *csin, int actual);
static Client* get_client(Client *clients, SOCKADDR_IN *csin, int actual);

static int check_if_client_exists(Client *clients, SOCKADDR_IN *csin, int actual)
{
   int i = 0;
   for(i = 0; i < actual; i++)
   {
      if(clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
	    && clients[i].sin.sin_port == csin->sin_port)
      {
	 return 1;
      }
   }

   return 0;
}

static Client* get_client(Client *clients, SOCKADDR_IN *csin, int actual)
{
   int i = 0;
   for(i = 0; i < actual; i++)
   {
      if(clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
	    && clients[i].sin.sin_port == csin->sin_port)
      {
	 return &clients[i];
      }
   }

   return NULL;
}

static void send_message_to_all_clients(int sock, Client *clients, Client *sender, int actual, const char *buffer, char from_server)
{
	int i = 0;
	char message[BUF_SIZE];
	message[0] = 0;
	for(i = 0; i < actual; i++)
	{
		if(sender != &clients[i])
		{
			if(from_server == 0)
			{
				strncpy(message, sender->name, BUF_SIZE - 1);
				strncat(message, " : ", sizeof message - strlen(message) - 1);
			}
			strncat(message, buffer, sizeof message - strlen(message) - 1);
			write_client(sock, &clients[i].sin, message);
		}
	}
}

static int read_client(SOCKET sock, SOCKADDR_IN *sin, char *buffer)
{
	int n = 0;
	int sinsize = sizeof *sin;

	if ((n = recvfrom(sock, buffer, BUF_SIZE - 1, 0, (SOCKADDR *) sin, &sinsize)) < 0)
	{
		// std::cout << "Erreur recvfrom()" << std::endl; 
		return -1;
	}
	buffer[n] = 0;

	return n;
}

static void write_client(SOCKET sock, SOCKADDR_IN *sin, const char *buffer)
{
	if (sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR *) sin, sizeof *sin) < 0)
	{
		std::cout << "Erreur send()" << std::endl; 
		return ;
	}
}

int main(int argc, char **argv)
{
	if (!Sockets::Start())
	{
		std::cout << "Erreur initialisation WinSock : " << Sockets::GetError();
		return -1;
	}

	// init socket
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // ipv4, UDP
	if (sock == INVALID_SOCKET)
	{
		std::cout << "Erreur initialisation socket : " << Sockets::GetError();
		return -2;
	}

	if (!Sockets::SetNonBlocking(sock))
	{
		std::cout << "Erreur settings non bloquant : " << Sockets::GetError();
		return -3;
	}

	SOCKADDR_IN server;
	server.sin_addr.s_addr = INADDR_ANY;  // indique que toutes les sources seront acceptées
	// UTILE: si le port est 0 il est assigné automatiquement
	server.sin_port = htons(PORT); // toujours penser à traduire le port en réseau
	server.sin_family = AF_INET; // notre socket est UDP

	if (bind(sock, (SOCKADDR *) &server, sizeof(server)) == SOCKET_ERROR)
	{
		std::cout << "Erreur bind : " << Sockets::GetError();
		return -3;
	}

	char buffer[BUF_SIZE];
	int actual = 0;
	int selectRedy;
	Client clients[MAX_CLIENTS];

	fd_set rdfs;
	timeval timeout = { 0 };

	while (1)
	{
		FD_ZERO(&rdfs);
		FD_SET(sock, &rdfs);
		selectRedy = select(sock + 1, &rdfs, nullptr, nullptr, &timeout);
		if (selectRedy == -1)
		{
			std::cout << "Erreur select : " << Sockets::GetError() << std::endl;
			return -4;
		}
		else if (selectRedy > 0)
		{
			if(FD_ISSET(sock, &rdfs))
			{
				/* new client */
				SOCKADDR_IN csin = { 0 };

				/* a client is talking */
				int ret = read_client(sock, &csin, buffer);
				if (ret == -1)
					continue;
				if (check_if_client_exists(clients, &csin, actual) == 0)
				{
					std::cout << "nouveau client" << std::endl;
					if (actual != MAX_CLIENTS)
					{
						Client c = { csin };
						strncpy(c.name, buffer, BUF_SIZE - 1);
						clients[actual] = c;
						actual++;
					}
				}
				else
				{
					std::cout << "Client info" << std::endl;
					std::cout << buffer << std::endl;

					Client *client = get_client(clients, &csin, actual);
					if(client == NULL) continue;
					int i = 0;
					while (i++ < 20) {
						write_client(sock, &client->sin, "ok");
						std::this_thread::sleep_for(std::chrono::milliseconds(200));
					}
					// send_message_to_all_clients(sock, clients, client, actual, buffer, 0);
				}
			}
	   }
	}

	Sockets::CloseSocket(sock);

	Sockets::Release();

	return EXIT_SUCCESS;
}

void initPort()
{
	/*
	struct sockaddr_in sin2;
	int addrlen = sizeof(sin2);
	if (getsockname(sock, (struct sockaddr *)&sin2, &addrlen) == 0 &&
		sin2.sin_family == AF_INET &&
		addrlen == sizeof(sin2))
	{
		int local_port = ntohs(sin2.sin_port);
	}*/
}