#include "server_socket.hpp"

ServerSocket::ServerSocket(int domain, int service, int protocol, int port, u_long interface) 
    : SimpleSocket(domain, service, protocol, port, interface) {}

ServerSocket::~ServerSocket() {
    close(getSock());
}

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
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
   int new_socket;
    while(1) {
        std::cout << "+++++++ Waiting for new connection ++++++++" << std::endl;

        // waits for a new TCP request and tests for error
        new_socket = accept(getSock(), (struct sockaddr*) getAddress(), getAddrlen());
        testSocket(new_socket);
        char buffer[30000] = {0};
        long valread = read( new_socket , buffer, 30000);

        std::cout << "Requested file: " << buffer << std::endl;
        int fd = open(buffer, O_RDONLY);
        if (fd < 0) {
            perror("Error");
            strcpy(buffer, "Error: file not found.");
            write(new_socket, buffer, strlen(buffer));
        } else {
            int bytesRead;
            while ((bytesRead = read(fd, buffer, sizeof buffer)) > 0) {
                write(new_socket, buffer, bytesRead);
            }
            close(fd);
            close(new_socket);
        }
        shutdown(new_socket, SHUT_WR);
    }
}