#include "client/client.h"
#include "server/server.h"
#include "socket/socket.h"
#include <cstring>

int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        if ((strcmp(argv[1], "server") == 0) && argc == 3)
        {
            Server s(Protocol::TCP, std::stoi(argv[2]));
            if (!s.start())
            {
                return 4;
            }
        }
        else if (strcmp(argv[1], "client") == 0 && argc == 4)
        {
            Client c(std::string(argv[2]), std::stoi(argv[3]), Protocol::TCP);
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
