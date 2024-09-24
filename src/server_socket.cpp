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
        
        if (new_socket < 0) {
            perror("Error: ");
            close(new_socket);
            continue;
        }
        handleRequest(new_socket);
    }
}

void ServerSocket::handleRequest(int req_fd) {
    char buffer[BUF_SIZE] = {0};
    long valread = read( req_fd , buffer, BUF_SIZE);

    std::string file_name(buffer);

    std::cout << "Requested file: " << buffer << std::endl;
    int fd = open(buffer, O_RDONLY);
    if (fd < 0) {
        perror("Error");
        strcpy(buffer, "Error: file not found.");
        write(req_fd, buffer, strlen(buffer));
    } else {
        std::cout << "File found: " << buffer << std::endl;
        int bytesRead;
        std::string data;
        while ((bytesRead = read(fd, buffer, sizeof buffer)) > 0) {
            data.append(buffer, bytesRead);
        }
        sort(data.begin(), data.end());
        ssize_t bytes_sent = 0;
        ssize_t total_bytes_sent = 0;
        size_t data_length = data.size();
        
        // Send data in a loop until the entire string is sent
        while (total_bytes_sent < data_length) {
            bytes_sent = send(req_fd, data.c_str() + total_bytes_sent, data_length - total_bytes_sent, 0);
            
            if (bytes_sent < 0) {
                std::cerr << "Error while sending data!" << std::endl;
                break;
            }
            total_bytes_sent += bytes_sent;
        }
        close(fd);
    }
    std::cout << "Response sent for: " << file_name << std::endl;
    close(req_fd);
}