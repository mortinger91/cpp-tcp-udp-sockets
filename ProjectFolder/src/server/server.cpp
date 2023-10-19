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

    std::cout << "Listening for a new connection request on port: " << m_Port
              << std::endl;
    if (!Socket::callListen(m_Passive_fd)) return false;

    std::string peerAddress;
    if (!Socket::callAccept(m_Passive_fd, m_Connection_fd, peerAddress))
        return false;
    std::cout << "Accepted a new connection from IP address: " << peerAddress
              << std::endl;

    std::string initialMessage = "Hello, client " + peerAddress + "!\n";
    if (!Socket::sendMessage(m_Connection_fd, initialMessage)) return false;
    std::cout << "Sent message: " << initialMessage;

    std::string receivedMessage;
    std::string input;
    bool returnValue = true;
    while (true)
    {
        std::getline(std::cin, input);
        if (input == "exit") break;
        if (!Socket::readMessage(m_Connection_fd, receivedMessage))
        {
            returnValue = false;
            break;
        }
        std::cout << "Received message: " << receivedMessage << std::endl;
        std::cout << "Message in hex: "
                  << Utility::rawBytesToHexString(receivedMessage) << std::endl;
    }

    Socket::callClose(m_Passive_fd);
    Socket::callClose(m_Connection_fd);
    return returnValue;
}
