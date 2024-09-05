#include "server_socket.hpp"

int main() {
    ServerSocket sock = ServerSocket(AF_INET, SOCK_STREAM, 0, PORT, INADDR_ANY);
    sock.init();
    std::cout << "Listening on port " << PORT << std::endl;
    sock.acceptConnections();
    return 0;
}