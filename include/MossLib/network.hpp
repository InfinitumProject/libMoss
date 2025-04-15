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
#define READY_PACKET "CMD_^[READY]"
#define EXIT_PACKET "CMD_^[EXIT]"
#define STOP_PACKET "CMD_^[STOP]"

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
        /**
         * @brief Constructs a new socket connection.
         * @param _address A string that contains an address, either an IP or hostname.
         * @param _port The port to connect on.
         * 
         * @return a socket connection fd.
         */
        static int constructConnection(std::string,int,int);
        
        /**
         * @brief Constructs a new socket connection and stores it in the class.
         * @param _address A string that contains an address, either an IP or hostname.
         * @param _port The port to connect on.
         * 
         * @return a socket connection fd.
         */
        TCP(std::string, int);

        /**
         * @brief Safely destroy a TCP object, handling all threads inside of it.
         */
        ~TCP();

        /**
         * @brief Gets how many bytes are avaliable to read from the socket.
         * 
         * @return The number of bytes.
         */
        int hasReadableData();

        /**
         * @brief Writes a string containing data to the socket safely (waits for the server to declare it is ready to recieve data).
         * 
         * @return A reference to itself so they can be chained together.
         */
        TCP &operator<<(std::string);

        /**
         * @brief Reads data from what the server has sent and writes it to the given string variable.
         * 
         * @return A reference to itself so they can be chained.
         */
        TCP &operator>>(std::string&);

        /**
         * @brief Just a universal error used to diagnose issues, will probably expand it into a struct
         * @brief with more descript errors in the future. (1 = Socket creation failure, 2 = Unsupported or invalid address, 3 = Failure to connect.)
         */
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

    //To do next: Implement TCP Server class with a virtual handler function to handle connections for multithreading capability.
    //Also: start with a single threaded server, and then expand to multithread. Build a good foundation, stop jumping in!!!
}