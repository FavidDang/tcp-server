#include "simple_socket.hpp"

SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface) {
    // Define address structure
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
    addrlen = sizeof(address);
    // Establish socket
    sock = socket(domain, service, protocol);
    testSocket(sock);
}

void SimpleSocket::init() {
    // Establish bind/connection
    connection = connectToNetwork(sock, (struct sockaddr *)&address);
    testSocket(connection);
}

void SimpleSocket::testSocket(int sock) {
    if (sock < 0) {
        perror("Error: ");
        exit(EXIT_FAILURE);
    }
}

struct sockaddr_in* SimpleSocket::getAddress() { return &address; }
int SimpleSocket::getSock() { return sock; }
int SimpleSocket::getConnection() { return connection; }
socklen_t* SimpleSocket::getAddrlen() { return &addrlen; }