#include "mtserver_socket.hpp"

MTServerSocket::MTServerSocket(int domain, int service, int protocol, int port, u_long interface) :
    ServerSocket(domain, service, protocol, port, interface) {}

void MTServerSocket::acceptConnections() {

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    int new_socket;
    while(1) {
        std::cout << "+++++++ Waiting for new connection ++++++++" << std::endl;

        // waits for a new TCP request and tests for error
        new_socket = accept(getSock(), (struct sockaddr*) getAddress(), getAddrlen());
        std::cout << "got new request" << std::endl;

        if (new_socket < 0) {
            perror("Error: ");
            close(new_socket);
            continue;
        }
        pthread_t thread;
        pthread_args* args = new pthread_args;
        args->server_ptr = this;
        args->req_fd = new_socket;
        int err = pthread_create(&thread, NULL, threadWrapper, args);
        if (err < 0) {
            perror("Error: ");
        } else {
            std::cout << "spinning new thread" << std::endl;
            pthread_detach(thread);
        }
    }

}

void* MTServerSocket::threadWrapper(void* args) {
    pthread_args* args_ptr = static_cast<pthread_args*>(args);
    MTServerSocket* server_instance = args_ptr->server_ptr;
    server_instance->handleRequest(args_ptr->req_fd);
    delete args_ptr;
}