#include "server_socket.hpp"
#include "mtserver_socket.hpp"
#include <csignal>

int main() {
    std::cout << "Please enter default or mtserver." << std::endl; 
    std::string server_type;
    std::getline(std::cin, server_type);

    if (server_type == "default") {
        ServerSocket sock = ServerSocket(AF_INET, SOCK_STREAM, 0, PORT, INADDR_ANY);
        sock.init();
        std::cout << "Default server listening on port " << PORT << std::endl;
        sock.acceptConnections();
    } else if (server_type == "mtserver") {
        MTServerSocket sock = MTServerSocket(AF_INET, SOCK_STREAM, 0, PORT, INADDR_ANY);
        sock.init();
        std::cout << "Multithreaded server listening on port " << PORT << std::endl;
        sock.acceptConnections();
    }

    return 0;
}