#pragma once

#include <optional>
#include <string>

enum Protocol
{
    TCP,
    UDP
};

namespace Socket
{
    bool create(const Protocol protocol, int& fileDescriptor);

    bool callBind(const int fileDescriptor, std::optional<const int> port,
                  std::optional<const std::string> address);

    // Listen for incoming connections.
    // The fileDescriptor passed is called a passive socket because
    // it is calling listen() and waiting for an active peer socket
    // to call connect() and establish a new connection
    //
    // the backlog argument represents the maximum number of pending
    // unaccepted connection that can be held in the OS internal queue
    bool callListen(const int fileDescriptorPassive, const int backlog = 5);

    // Accept an incoming connection.
    // accept() creates a new socket that will be connected
    // to the peer active socket (the client) that performed the connect().
    // This call will block until a peer socket calls connect().
    //
    // Side note: If a client calls connect() in between
    // listen() and accept() the OS will mark it as a pending
    // connection and the client connect() will block until
    // the server calls accept()
    bool callAccept(const int fileDescriptorPassive, int& fileDescriptor,
                    std::string& peerAddress);

    // The socket that calls connect() is called an active socket (the client),
    // since it is actively performing the connect() to the peer socket.
    // The peer socket is called passive (the server),
    // since it calls listen() and wait for the peer socket to call connect()
    bool callConnect(const int fileDescriptorConnection,
                     const std::string& endpointAddress,
                     const int endpointPort);

    bool sendMessage(const int fileDescriptor, const std::string& message);

    // recv() is a blocking call
    bool callRecv(const int fileDescriptor, std::string& message,
                  const int bufferSize = 1024);

    bool callRecvfrom(const int fileDescriptor, std::string& sourceAddress,
                      std::string& message, const int bufferSize = 1024);

    void callClose(const int fileDescriptor);
}  // namespace Socket
