#include "../../include/libMoss/network.hpp"
#include "../../include/libMoss/debug.hpp"

using namespace Moss::Debug;
using namespace std::chrono_literals;

int server(int port) {
    dprint("Server:\tInitializing server...");
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2.5s);
    bool running = true;
    std::vector<std::thread> threads;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    //char buffer[65535] = {0};

    dprint("Server:\tCreating socket...");
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << "socket failed" << std::endl;
        return 1;
    }

    dprint("Server:\tSetting socket options...");
    dprint("\t\tDev Note: Not sure what setting options does, need to do research.");
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cout << "setsockopt" << std::endl;
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    dprint("Server:\tBinding to address and port...");
    // Bind socket to address and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cout << "bind failed" << std::endl;
        return 1;
    }

    dprint("Server:\tListening on port...");
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        std::cout << "listen failed" << std::endl;
        return 1;
    }

    
    std::function<void(int)> handler = [](int new_socket){
        dprint("Server:\tStarting handler for new socket: \"",false); dprint(new_socket,false); dprint("\"...");
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
    
    dprint("Server:\tAccepting new connections...");
    // Accept connections
    while (running){
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) >= 0) {
            dprint("Server:\tAccepted connection: \"",false); dprint(new_socket,false); dprint("\"");
            threads.push_back(std::thread(handler, new_socket));
        }
    }
    
    dprint("Server:\tRunning loop broken! Deconstructing server...");
    for (std::vector<std::thread>::iterator it = threads.begin(); it != threads.end(); it++){
        dprint("Server:\tFound thread! Checking joinability...");
        if ((*it).joinable()){
            dprint("Server:\tThread is joinable...");
            (*it).join();
            threads.erase(it);
        } else {
            dprint("Server:\tWarning:\tThread is not joinable!");
        }
    }
    
    // Close socket
    dprint("Server:\tClosing socket...");
    close(server_fd);

    dprint("Server:\tChecking status of server threads...");
    if (threads.size()){
        dprint("Server:\tWarning:\tThreadpool is larger than 0!! This may halt the program!!!");
    }
    return 0;
}

#include <chrono>
#include <functional>

int main(){
    try {
        std::thread e(&server,1234);
        
        std::this_thread::sleep_for(2.5s);

        Moss::Network::TCP conn1("127.0.0.1",1234);
        Moss::Network::TCP conn2("127.0.0.1",1234);
        
        conn1 << "This is a test from C1.";
        conn1 << "EWAEWEADAS";
        conn1 << EXIT_PACKET;
        conn2 << "This is a test from C2.";
        conn2 << "Ooooh.. keysmash... ABGAJSBGJBAG!!!!";
        conn2 << EXIT_PACKET;
        
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        Moss::Network::TCP closer("127.0.0.1",1234);
        closer << STOP_PACKET;
        e.join();
        return 0;
    } catch (...) {
        return -1;
    }
}