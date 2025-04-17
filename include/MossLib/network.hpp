#pragma once
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <string> 
#include <chrono>
#include <thread>
#include <functional>
#ifdef __linux
#include <arpa/inet.h>
#include <sys/socket.h>
#elif _WIN32
#endif
#define READY_PACKET "CMD_^[READY]"
#define EXIT_PACKET "CMD_^[EXIT]"
#define STOP_PACKET "CMD_^[STOP]"

namespace Moss::Network {

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

    };
    
    /**
     * @brief A namespace containing all of the errors relating to sockets and TCP connections.
     */
    namespace socketError{
        class socketCreationError : public std::exception {
            public:
            const char *what() const noexcept override {
                return "Error: Could not create socket!";
            }
        };
        class socketAddressError : public std::exception {
            public:
            const char *what() const noexcept override {
                return "Error: Unsupported or invalid address!";
            }
        };
        class socketConnectionError : public std::exception {
            public:
            const char *what() const noexcept override {
                return "Error: Could not connect!";
            }
        };
        class socketOtherError : public std::exception {
            public:
            const char *what() const noexcept override {
                return "Error: Unspecified error!";
            }
        };
    }


    //To do next: Implement TCP Server class with a virtual handler function to handle connections for multithreading capability.
    //Also: start with a single threaded server, and then expand to multithread. Build a good foundation, stop jumping in!!!
}