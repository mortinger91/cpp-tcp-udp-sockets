#pragma once

#include "socket/socket.h"

class Server
{
   public:
    Server(int _port, Protocol _protocol);
    void start();

   private:
    Protocol m_Protocol;
    int m_Port;
    int m_Listen_fd;
    int m_Server_fd;

    void createSocket(int port, Protocol protocol);
    void createTCPSocket(int port);
};
