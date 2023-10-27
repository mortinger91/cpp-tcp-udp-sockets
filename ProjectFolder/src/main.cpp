#include "client/client.h"
#include "server/server.h"
#include "socket/socket.h"
#include <cstring>

int main(int argc, char* argv[])
{
    if (argc >= 3)
    {
        Protocol protocol;
        if (strcmp(argv[2], "tcp") == 0)
        {
            protocol = Protocol::TCP;
        }
        else if (strcmp(argv[2], "udp") == 0)
        {
            protocol = Protocol::UDP;
        }
        else
        {
            return 5;
        }

        if ((strcmp(argv[1], "server") == 0) && argc == 4)
        {
            Server s(protocol, std::stoi(argv[3]));
            if (!s.start())
            {
                return 4;
            }
        }
        else if (strcmp(argv[1], "client") == 0 && argc == 5)
        {
            Client c(protocol, std::string(argv[3]), std::stoi(argv[4]));
            if (!c.start())
            {
                return 3;
            }
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
