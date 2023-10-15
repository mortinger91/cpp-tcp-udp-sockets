#pragma once

#include "socket/socket.h"
#include <string>

class Client
{
   public:
    Client(std::string _address, int _port, Protocol _protocol);
    void start();

   private:
    Protocol m_Protocol;
    std::string m_Address;
    int m_Port;
    int m_Client_fd;

    void createSocketAndConnect(std::string address, int port,
                                Protocol protocol);
    void createTCPSocketAndConnect(std::string address, int port);
};
