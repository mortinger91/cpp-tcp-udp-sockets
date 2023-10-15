// main.cpp: This file contains the 'main' function.
// Program execution begins and ends there.

#include "client/client.h"
#include "server/server.h"
#include "socket/socket.h"
#include <cstring>

int main(int argc, char* argv[])
{
    if(argc >= 2)
    {
        if(strcmp(argv[1], "server") == 0)
        {
            Server s(9000, Protocol::TCP);
            s.start();
        }
        else if(strcmp(argv[1], "client") == 0)
        {
            Client c("127.0.0.1", 9000, Protocol::TCP);
            c.start();
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 1;
    }

    return 0;
}
