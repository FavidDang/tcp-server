#include "server_socket.hpp"

ServerSocket::ServerSocket(int domain, int service, int protocol, int port, u_long interface) 
    : SimpleSocket(domain, service, protocol, port, interface) {}

int ServerSocket::connectToNetwork(int sock, struct sockaddr * address) {
    if (bind(sock, address, sizeof(*address)) < 0) {
        perror("Bind failed");
        return -1;
    }
    if (listen(sock, MAX_REQUESTS) < 0) {
        perror("Listen failed");
        return -1;
    }
    return 0;
}

void ServerSocket::acceptConnections() {
   char* hello = "Hello from the server!";
   int new_socket;
    while(1) {
        std::cout << "+++++++ Waiting for new connection ++++++++" << std::endl;
        new_socket = accept(getSock(), (struct sockaddr*) getAddress(), getAddrlen());
        testSocket(new_socket);
        char buffer[30000] = {0};
        long valread = read( new_socket , buffer, 30000);
        std::cout << valread << std::endl;
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
}