#include "../../include/MossLib/network.hpp"

int server(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[65535] = {0};
    const char* message = "Hello from server";

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << "socket failed" << std::endl;
        return 1;
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cout << "setsockopt" << std::endl;
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind socket to address and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cout << "bind failed" << std::endl;
        return 1;
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        std::cout << "listen failed" << std::endl;
        return 1;
    }

    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        std::cout << "accept failed" << std::endl;
        return 1;
    }

    // Read and send data
    while (buffer != "exit"){
        memset(buffer,0,sizeof(buffer));
        buffer[0] = '\0';
        recv(new_socket, buffer, 65535, 0);
        std::cout << "Received: " << buffer << std::endl;
        send(new_socket, buffer, strlen(buffer), 0);
        std::cout << "Message sent" << std::endl;
    }

    // Close socket
    close(new_socket);
    close(server_fd);
    return 0;
}

using namespace std::chrono_literals;

int main(){
    std::thread serverT(&server,12345);
    Moss::Network::TCP test("127.0.0.1",12345);
    std::string buff;
    test << "eaea";
    std::this_thread::sleep_for(0.2s);
    test >> buff;
    std::cout << buff << std::endl;
    test << "wawawa";
    std::this_thread::sleep_for(0.2s);
    test >> buff;
    std::cout << buff << std::endl;
    test << "exit";
    serverT.join();
    //test << "exit";
    //test << "exit";
    test.closeConnection();
    return 0;
}