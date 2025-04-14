#pragma once
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <string> 
#include <chrono>
#include <thread>
#ifdef __linux
#include <arpa/inet.h>
#include <sys/socket.h>
#elif _WIN32
#endif

namespace Moss::Network {

    using namespace std::chrono_literals;
    class TCP {
        bool is_running = true, is_server_ready = false;
        int _connection_fd;
        std::vector<std::string> _write_buffer;
        std::string _read_buffer = "";
        std::vector<std::thread> _threads;
        void startBufferListener();
        public:
        static int constructConnection(std::string,int);
        TCP(std::string, int);
        ~TCP();

        int hasReadableData();

        TCP &operator<<(std::string);
        TCP &operator>>(std::string&);

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