#pragma once

#include "socket/socket.h"

class Server
{
   public:
    Server(const Protocol _protocol, const int _port);
    bool start();

   private:
    Protocol m_Protocol;
    int m_Port;
    int m_Passive_fd;
    int m_Connection_fd;
};
