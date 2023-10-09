#pragma once

#include "utility/definitions.h"

class Server {
public:
	Server(int _port, Protocol _protocol);
	void start();

private:
	Protocol m_Protocol;
	int m_Port;
	int m_Server_fd;
	int m_Client_fd;

	void createSocket(int port, Protocol protocol);
	void createTCPSocket(int port);
};