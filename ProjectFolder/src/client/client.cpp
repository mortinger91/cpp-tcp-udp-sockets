#include "client.h"

#include "utility/utility.h"
#include <arpa/inet.h>  // Include this header for inet_pton
#include <cstdlib>      // Include this header for exit()
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

Client::Client(std::string _address, int _port, Protocol _protocol)
    : m_Address(_address), m_Port(_port), m_Protocol(_protocol)
{
}

bool Client::start()
{
    std::cout << "Client started!" << std::endl;

    if (!createSocketAndConnect(m_Address, m_Port, m_Protocol))
    {
        return false;
    }

    // Send a message to the server
    std::string message = "Hello, server!\n";
    send(m_Client_fd, message.c_str(), message.length(), 0);
    std::cout << "Sent message: " << message << std::endl;

    char buffer[1024];
    ssize_t received = 0;
    while (true)
    {
        // Receive a message from the client
        received = recv(m_Client_fd, buffer, 1024, 0);
        if (received == 0)
        {
            std::cout << "Client disconnected!" << std::endl;
            break;
        }
        else if (received < 0)
        {
            std::cout << "Error receiving message!" << std::endl;
            break;
        }
        else
        {
            // string containing the packet's raw bytes
            std::string bufferString;
            for (int i = 0; buffer[i] != '\n' && i < 1024; i++)
            {
                bufferString += buffer[i];
            }
            // transform the raw bytes into hex
            std::string hexString = Utility::rawBytesToHexString(buffer, 1024);

            std::cout << "Client said (in hex): " << hexString << std::endl;
        }
    }

    // Close the socket
    close(m_Client_fd);
    return true;
}

bool Client::createSocketAndConnect(std::string address, int port,
                                    Protocol protocol)
{
    bool result = false;
    switch (protocol)
    {
        case Protocol::TCP:
            result = createTCPSocketAndConnect(address, port);
            break;
        case Protocol::UDP:
            break;
        case Protocol::UNIX:
            break;
    }
    return result;
}

bool Client::createTCPSocketAndConnect(std::string address, int port)
{
    // Creating the socket file descriptor
    m_Client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in socket_address
    {
    };
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);

    // Convert the server address from string to binary form
    auto result =
        inet_pton(AF_INET, address.c_str(), &(socket_address.sin_addr));
    if (result <= 0)
    {
        std::cerr << "Invalid server address!" << std::endl;
        close(m_Client_fd);
        return false;
    }

    // This is called an active socket since it is
    // performing the connect() to a passive socket.
    // A passive socket in one calling listen()
    if (connect(m_Client_fd, (struct sockaddr*)&socket_address,
                sizeof(socket_address)) < 0)
    {
        std::cerr << "Failed to connect to the server!" << std::endl;
        close(m_Client_fd);
        return false;
    }
    return true;
}
