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

    // TCP AND UDP:
    //   It is possible to call bind() here specifying a network
    //   interface IP address.
    //   This will force the socket to use that interface.
    //   Otherwise, the OS will decide which interface to use based
    //   on routing tables
    //
    // if (!Socket::callBind(m_Active_fd, std::nullopt, "192.168.1.123"))
    //    return false;

    // UDP:
    //   If the socket type is UDP(SOCK_DGRAM), it is not mandatory to call
    //   connect() as for TCP. If called, it causes the kernel to record the
    //   address as the socket peer, making it a "connected datagram socket".
    //   This enables the use of send() and recv().
    //   Only datagrams sent by the peer socket may be read on this socket.
    //   This is valid only on the socket on which connect() has been called,
    //   so the peer socket might not have called connect().
    //
    //   An "unconnected datagram socket" can receive datagrams from multiple
    //   addresses.
    //   recvfrom() must be used instead of recv() to read.
    //   sendto() must be used instead of send() to write.
    //
    //   connect() can be called again to change the address of the peer socket
    //
    if (!Socket::callConnect(m_Active_fd, m_Address, m_Port)) return false;

    std::string initialMessage = "Hello, server!\n";
    if (!Socket::sendMessage(m_Active_fd, initialMessage)) return false;
    std::cout << "Sent message: " << initialMessage;

    bool returnValue = true;
    std::string receivedMessage;
    while (true)
    {
        returnValue = Socket::readMessage(m_Active_fd, receivedMessage);
        if (!returnValue) break;
        std::cout << "Received message: " << receivedMessage;
        std::cout << "Message in hex: "
                  << Utility::rawBytesToHexString(receivedMessage) << std::endl
                  << std::endl;
    }

    Socket::callClose(m_Active_fd);
    return returnValue;
}
