#pragma once

enum Protocol {UDP, TCP, UNIX};

class Server {
public:
	Server(int _port, Protocol _protocol);
	void start();

private:
	Protocol m_Protocol;
	int m_Port;
	int m_Server_fd;
	int m_Client_fd;

	void createSocket(Protocol protocol, int port);
	void createTCPSocket(int port);
};