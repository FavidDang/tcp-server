#ifndef simple_socket_hpp
#define simple_socket_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

class SimpleSocket {
    struct sockaddr_in address;
    int sock;
    int connection;
    public:
        SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
        virtual int connectToNetwork(int sock, struct sockaddr_in address) = 0;
        void testSocket(int sock);
        struct sockaddr_in getAddress();
        int getSock();
        int getConnection();
};

#endif