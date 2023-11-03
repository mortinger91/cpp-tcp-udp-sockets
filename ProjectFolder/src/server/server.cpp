#include "server.h"

#include "utility/utility.h"
#include <iostream>

Server::Server(Protocol _protocol, int _port)
    : m_Protocol(_protocol), m_Port(_port)
{
}

bool Server::start()
{
    std::cout << "Server started!" << std::endl;

    if (!Socket::create(m_Protocol, m_Bound_fd)) return false;

    if (!Socket::callBind(m_Bound_fd, m_Port, std::nullopt)) return false;

    // TCP:
    //   listen() and accept() are used only in TCP(SOCK_STREAM) sockets.
    //   Two file descriptors are needed, the passive one will be used to
    //   listen() and accept() new connections.
    //   Every time a new connection is accepted, a new file descriptor
    //   representing that connection will be created.
    //   It is possible to iterate over accept() creating new
    //   connections over the same passive file descriptor
    //
    // UDP:
    //   A UDP socket is connection-less so data can be read from it after
    //   calling bind().
    //   Multiple endpoints can send data to this UDP socket
    std::string peerAddress;
    if (m_Protocol == Protocol::TCP)
    {
        std::cout << "Listening for a new TCP connection request on port: "
                  << m_Port << std::endl;
        if (!Socket::callListen(m_Bound_fd)) return false;

        if (!Socket::callAccept(m_Bound_fd, m_Connection_fd, peerAddress))
            return false;
        std::cout << "Accepted a new connection from IP address: "
                  << peerAddress << std::endl;

        std::string initialMessage = "Hello, client " + peerAddress + "!\n";
        if (!Socket::sendMessage(m_Connection_fd, initialMessage)) return false;
        std::cout << "Sent message: " << initialMessage;
    }
    else
    {
        std::cout << "Listening for UDP traffic on port: " << m_Port
                  << std::endl;
    }

    bool returnValue;
    std::string receivedMessage;
    while (true)
    {
        if (m_Protocol == Protocol::TCP)
            returnValue = Socket::callRecv(m_Connection_fd, receivedMessage);
        else
            returnValue =
                Socket::callRecvfrom(m_Bound_fd, peerAddress, receivedMessage);

        if (!returnValue) break;
        std::cout << "Received message: " << receivedMessage
                  << " from address: " << peerAddress;
        std::cout << "Message in hex: "
                  << Utility::rawBytesToHexString(receivedMessage) << std::endl
                  << std::endl;
    }

    if (m_Protocol == Protocol::TCP) Socket::callClose(m_Connection_fd);
    Socket::callClose(m_Bound_fd);
    return returnValue;
}
