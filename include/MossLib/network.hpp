#pragma once
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <string> 
#include <thread>
#include <chrono>

namespace Moss::Network {

    using namespace std::chrono_literals;
    class TCP {
        int _socket = 0;
        struct sockaddr_in server_addr;
        public:
        int retryCount;
        std::chrono::milliseconds retryTime;
        TCP(std::string,int,int = 5,std::chrono::milliseconds = 250ms);
        ~TCP();

        std::string r();
        void w(std::string);

        TCP &operator<<(std::string&);
        TCP &operator>>(std::string&);
        TCP &operator<<(const char[]);
        TCP &operator<<(char[]);

        void closeConnection();

        class socketError : public std::exception {
            public:
            int _error;
            socketError(int errorCode = 0) : _error(errorCode) {}
            const char *what() const noexcept override {
                switch (this->_error) {                
                case 1:
                    return "Error: Could not create socket!";
                    break;

                case 2:
                    return "Error: Unsupported or invalid address!";
                    break;

                case 3:
                    return "Error: Could not connect!";
                    break;
                default:
                    return "Error: Unspecified error!";
                    break;
                }
            }
        };
    };
}

/*int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    const char* hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\n Socket creation error \n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n";
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";
    valread = read(sock, buffer, 1024);
    std::cout << buffer << std::endl;
    close(sock);
    return 0;
}*/