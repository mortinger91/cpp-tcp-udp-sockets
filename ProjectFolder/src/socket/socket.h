#pragma once

#include <optional>

enum Protocol
{
    TCP,
    UDP
};

class Socket
{
    bool create(const Protocol protocol, int& fileDescriptor);

    bool callBind(const int fileDescriptor, std::optional<const int> port,
                  std::optional<const std::string> address);

    // Listen for incoming connections.
    // The fileDescriptor passed is called a passive socket because
    // it is calling listen() and waiting for an active peer socket
    // to call connect() and establish a new connection
    //
    // the backlog parameters represent the maximum number of pending
    // unaccepted connection that can be held in the OS internal queue
    bool callListen(const int fileDescriptor, const int backlog = 5);

    // Accept an incoming connection.
    // accept() creates a new socket that will be connected
    // to the peer active socket (the client) that performed the connect().
    // This call will block until a peer socket calls connect().
    //
    // Side note: If a client calls connect() in between
    // listen() and accept() the OS will mark it as a pending
    // connection and the client connect() will block until
    // the server calls accept()
    bool callAccept(const int fileDescriptorPassive, int& fileDescriptorActive,
                    std::string& peerSocketAddress);

    bool sendMessage(const int fileDescriptor, const std::string& message);

    // recv() is a blocking call
    bool readMessage(const int fileDescriptor, std::string& message,
                     const int bufferSize = 1024);
};
