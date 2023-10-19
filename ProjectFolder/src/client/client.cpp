#include "client.h"

#include "utility/utility.h"
#include <arpa/inet.h>  // Include this header for inet_pton
#include <cstdlib>      // Include this header for exit()
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

Client::Client(const Protocol _protocol, const std::string& _address,
               const int _port)
    : m_Protocol(_protocol), m_Address(_address), m_Port(_port)
{
}

bool Client::start()
{
    std::cout << "Client started!" << std::endl;

    if (!Socket::create(m_Protocol, m_Active_fd)) return false;

    // It is possible to callBind() here specifying a network interface address.
    // This will force the socket to use that interface, ignoring the default
    // system routing

    if (!Socket::callConnect(m_Active_fd, m_Address, m_Port)) return false;

    std::string initialMessage = "Hello, server!\n";
    if (!Socket::sendMessage(m_Active_fd, initialMessage)) return false;
    std::cout << "Sent message: " << initialMessage;

    bool returnValue = true;
    std::string receivedMessage;
    while (true)
    {
        // std::string input;
        // std::getline(std::cin, input);
        // if (input == "exit") break;

        if (!Socket::readMessage(m_Active_fd, receivedMessage))
        {
            returnValue = false;
            break;
        }
        std::cout << "Received message: " << receivedMessage;
        std::cout << "Message in hex: "
                  << Utility::rawBytesToHexString(receivedMessage) << std::endl
                  << std::endl;
    }

    Socket::callClose(m_Active_fd);
    return returnValue;
}
