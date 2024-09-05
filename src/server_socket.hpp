#ifndef server_socket_hpp
#define server_socket_hpp

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "simple_socket.hpp"

#define MAX_REQUESTS 10
#define PORT 8080

class ServerSocket: public SimpleSocket {
    public:
        ServerSocket(int domain, int service, int protocol, int port, u_long interface);
        int connectToNetwork(int sock, struct sockaddr * address) override;
        void acceptConnections();
};

#endif