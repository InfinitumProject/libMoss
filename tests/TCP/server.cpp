#include "../../include/libMoss/network.hpp"
#include "../../include/libMoss/debug.hpp"
int server(int port) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2.5s);
    bool running = true;
    std::vector<std::thread> threads;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    //char buffer[65535] = {0};

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

    
    std::function<void(int)> handler = [](int new_socket){
        char buffer[65535];
        for (;;){
            write(new_socket, READY_PACKET, strlen(READY_PACKET));
            dprint("Server:\tSent ready signal!");
            memset(buffer,0,sizeof(buffer));
            buffer[0] = '\0';
            recv(new_socket, buffer, 65535, 0);
            std::cout << "Server:\tReceived: " << buffer << std::endl;
            send(new_socket, buffer, strlen(buffer), 0);
            dprint("Server:\tMessage sent");
            if ((strncmp(buffer, EXIT_PACKET, strlen(EXIT_PACKET))) == 0){
                write(new_socket, EXIT_PACKET, strlen(EXIT_PACKET));
                break;
            }
            if ((strncmp(buffer, STOP_PACKET, strlen(STOP_PACKET))) == 0){
                write(new_socket, EXIT_PACKET, strlen(EXIT_PACKET));
                exit(0);
                break;
            }
        }
        close(new_socket);
    };
    
    // Accept connections
    while (running){
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) >= 0) {
            threads.push_back(std::thread(handler, new_socket));
        }
    }
    
    for (auto &th : threads){
        if (th.joinable()){
            th.join();
        }
    }
    // Close socket
    close(server_fd);
    return 0;
}