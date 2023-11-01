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

    if (!Socket::create(m_Protocol, m_Passive_fd)) return false;

    if (!Socket::callBind(m_Passive_fd, m_Port, std::nullopt)) return false;

    // listen() and accept() are required only for a TCP(SOCK_STREAM) socket.
    // A UDP socket is connection-less so data can be read after calling bind()
    if (m_Protocol == Protocol::TCP)
    {
        std::cout << "Listening for a new TCP connection request on port: "
                  << m_Port << std::endl;
        if (!Socket::callListen(m_Passive_fd)) return false;

        std::string peerAddress;
        if (!Socket::callAccept(m_Passive_fd, m_Connection_fd, peerAddress))
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
            returnValue = Socket::readMessage(m_Connection_fd, receivedMessage);
        else
            returnValue = Socket::readMessage(m_Passive_fd, receivedMessage);

        if (!returnValue)
        {
            break;
        }
        std::cout << "Received message: " << receivedMessage;
        std::cout << "Message in hex: "
                  << Utility::rawBytesToHexString(receivedMessage) << std::endl
                  << std::endl;
    }

    if (m_Protocol == Protocol::TCP) Socket::callClose(m_Connection_fd);
    Socket::callClose(m_Passive_fd);
    return returnValue;
}
