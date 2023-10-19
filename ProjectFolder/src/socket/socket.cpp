#include "socket.h"

#include <arpa/inet.h>
#include <cerrno>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

bool Socket::create(const Protocol protocol, int& fileDescriptor)
{
    // 0 means the socket will use the default protocol for the address family
    switch (protocol)
    {
        case Protocol::TCP:
            fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
            break;
        case Protocol::UDP:
            fileDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
            break;
    }
    return (fileDescriptor != -1);
}

bool Socket::callBind(const int fileDescriptor, std::optional<const int> port,
                      std::optional<const std::string> address)
{
    struct sockaddr_in addr
    {
    };
    addr.sin_family = AF_INET;
    if (address)
        addr.sin_addr.s_addr = inet_addr((*address).c_str());
    else
        addr.sin_addr.s_addr = INADDR_ANY;   // Bind on all available interfaces
    if (port) addr.sin_port = htons(*port);  // Listen on the specified port

    // To receive new incoming packets or connections,
    // the socket must be bound to a local interface address and port
    if (bind(fileDescriptor, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "bind() returned an error: " << errno << std::endl;
        close(fileDescriptor);
        return false;
    }
    return true;
}

bool Socket::callListen(const int fileDescriptorPassive, const int backlog)
{
    if (listen(fileDescriptorPassive, backlog) < 0)
    {
        std::cerr << "listen() returned an error: " << errno << std::endl;
        close(fileDescriptorPassive);
        return false;
    }
    return true;
}

bool Socket::callAccept(const int fileDescriptorPassive, int& fileDescriptor,
                        std::string& peerSocketAddress)
{
    struct sockaddr_in addr
    {
    };
    socklen_t addr_size = sizeof(addr);
    fileDescriptor =
        accept(fileDescriptorPassive, (struct sockaddr*)&addr, &addr_size);
    if (fileDescriptor < 0)
    {
        std::cerr << "accept() returned an error: " << errno << std::endl;
        close(fileDescriptorPassive);
        close(fileDescriptor);
        return false;
    }
    char peerSocketAddressC[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), peerSocketAddressC, INET_ADDRSTRLEN);
    peerSocketAddress = std::string(peerSocketAddressC);
    return true;
}

bool Socket::callConnect(const int fileDescriptor,
                         const std::string& endpointAddress,
                         const int endpointPort)
{
    struct sockaddr_in addr
    {
    };
    addr.sin_family = AF_INET;
    addr.sin_port = htons(endpointPort);
    // Convert the server address from string to binary form
    if (inet_pton(AF_INET, endpointAddress.c_str(), &(addr.sin_addr)) <= 0)
    {
        std::cerr << "Invalid server address!" << std::endl;
        close(fileDescriptor);
        return false;
    }

    if (connect(fileDescriptor, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "connect() returned an error: " << errno << std::endl;
        close(fileDescriptor);
        return false;
    }
    return true;
}

bool Socket::sendMessage(const int fileDescriptor, const std::string& message)
{
    ssize_t sent = send(fileDescriptor, message.c_str(), message.length(), 0);
    if (sent < 0)
    {
        std::cerr << "An error occurred during send(): " << errno << std::endl;
        return false;
    }
    else if (sent == 0)
    {
        std::cout << "send(): The connection has been closed gracefully by the "
                     "peer, closing the socket!"
                  << std::endl;
        close(fileDescriptor);
        return false;
    }
    else if (sent < message.length())
    {
        std::cout << "send(): Not all data has been sent" << std::endl;
    }
    return true;
}

bool Socket::readMessage(const int fileDescriptor, std::string& message,
                         const int bufferSize)
{
    char buffer[bufferSize];
    // 4th argument is flags. We currently set it to 0
    ssize_t received = recv(fileDescriptor, buffer, bufferSize, 0);
    if (received < 0)
    {
        std::cerr << "An error occurred during recv(): " << errno << std::endl;
        return false;
    }
    else if (received == 0)
    {
        std::cout << "recv(): The connection has been closed gracefully by the "
                     "peer, closing the socket!"
                  << std::endl;
        close(fileDescriptor);
        return false;
    }
    message = std::string(buffer);
    // This is needed otherwise the string will contain some garbage
    // from previous messages and won't automatically resize to the
    // first /n character.
    message.resize(received);
    return true;
}

void Socket::callClose(const int fileDescriptor)
{
    close(fileDescriptor);
}
