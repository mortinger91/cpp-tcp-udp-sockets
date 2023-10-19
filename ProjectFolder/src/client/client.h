#pragma once

#include "socket/socket.h"
#include <string>

class Client
{
   public:
    Client(const Protocol _protocol, const std::string& _address,
           const int _port);
    bool start();

   private:
    Protocol m_Protocol;
    std::string m_Address;
    int m_Port;
    int m_Active_fd;
};
