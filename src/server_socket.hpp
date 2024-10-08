#ifndef server_socket_hpp
#define server_socket_hpp

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "simple_socket.hpp"

#define MAX_REQUESTS 100
#define PORT 8080

class ServerSocket: public SimpleSocket {
    public:
        ServerSocket(int domain, int service, int protocol, int port, u_long interface);
        ~ServerSocket();
        int connectToNetwork(int sock, struct sockaddr * address) override;
        virtual void acceptConnections();
        void handleRequest(int req_fd);
};

#endif