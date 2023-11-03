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
    // This file descriptor is used in both TCP and UDP.
    // - in TCP: This is the passive file descriptor used
    //           to listen() and accept() new connections
    // - in UDP: Since it is a connection-less protocol,
    //           there is only 1 file descriptor which is
    //           used straight after bind()
    int m_Bound_fd;
    // This file descriptor is used only in TCP.
    // It represents a connection established with a peer
    // and it is created when calling accept()
    int m_Connection_fd;
};
