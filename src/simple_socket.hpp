#ifndef simple_socket_hpp
#define simple_socket_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <algorithm>
#include <unistd.h>

const int BUF_SIZE = 8192;

class SimpleSocket {
    struct sockaddr_in address;
    socklen_t addrlen;
    int sock;
    int connection;
    public:
        char PWD[1024];
        virtual int connectToNetwork(int sock, struct sockaddr * address) = 0;
        SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
        void init();
        void testSocket(int sock);
        struct sockaddr_in* getAddress();
        socklen_t* getAddrlen();
        int getSock();
        int getConnection();
};

#endif