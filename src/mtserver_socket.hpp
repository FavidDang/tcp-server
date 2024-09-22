#ifndef mtserver_socket_hpp
#define mtserver_socket_hpp

#include "server_socket.hpp"
#include <pthread.h>

class MTServerSocket : public ServerSocket {

    static void* threadWrapper(void* server_ptr);

    public:
        MTServerSocket(int domain, int service, int protocol, int port, u_long interface);
        void acceptConnections() override;
};

struct pthread_args {
    MTServerSocket* server_ptr;
    int req_fd;
};

#endif