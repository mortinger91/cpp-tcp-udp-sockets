#include "server.h"

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(int _port, Protocol _protocol): 
    m_Port(_port), m_Protocol(_protocol) {}

void Server::start() {
	std::cout << "Server started!" << std::endl;

    createSocket(m_Protocol, m_Port);
	
    // Listen for incoming connections
	std::cout << "Listening for a new connection request!" << std::endl;
    listen(m_Server_fd, 5);

    // Accept an incoming connection
    m_Client_fd = accept(m_Server_fd, NULL, NULL);
	std::cout << "Accepted client connection!" << std::endl;

    // Send a message to the client
    std::string message = "Hello, client!\n";
	send(m_Client_fd, message.c_str(), message.length(), 0);
    std::cout << "Sent message: " << message << std::endl;

    char buffer[1024];
    while(true) {
		// Receive a message from the client
        recv(m_Client_fd, buffer, 1024, 0);
		{
            std::string bufferString;      
			for(int i = 0; buffer[i] != '\n' && i < 1024; i++) {
                bufferString+=buffer[i];
			}
            std::cout << "Client said: " << bufferString << std::endl;
		}
    }

    // Close the socket
	close(m_Client_fd);
    close(m_Server_fd);
}

void Server::createSocket(Protocol protocol, int port) {
	switch(protocol) {
		case Protocol::TCP:
			createTCPSocket(port);
			break;
		case Protocol::UDP:
			break;
		case Protocol::UNIX:
			break;
	}
}

void Server::createTCPSocket(int port) {
	// Create a socket
    m_Server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Bind the socket to an IP and port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on any IP
    address.sin_port = htons(port); // Listen on port
    bind(m_Server_fd, (struct sockaddr *)&address, sizeof(address));
}