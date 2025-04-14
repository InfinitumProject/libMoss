#include "../include/MossLib/network.hpp"
#include "../include/MossLib/debug.hpp"

#ifdef __linux

#include <sys/ioctl.h>

namespace Moss::Network {

    int TCP::constructConnection(std::string _address, int _port){
        int sockfd, connfd;
        struct sockaddr_in servaddr, cli;

        // socket create and verification
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            dprint("Client:\tsocket creation failed...");
            exit(0);
        }
        else
            dprint("Client:\tSocket successfully created..");
        bzero(&servaddr, sizeof(servaddr));

        // assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(_port);

        // connect the client socket to server socket
        if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
            dprint("Client:\tConnection with the server failed...");
            exit(0);
        }
        else {
            dprint("Client:\tConnected to the server...");
            return sockfd;
        }
    }

    void TCP::startBufferListener(){
        auto listener = [&](){
            char buff[65535];
            /*for (int n = 0;;) {
                bzero(buff, sizeof(buff));
                printf("Enter the string : ");
                n = 0;
                while ((buff[n++] = getchar()) != '\n');
                write(this->_connection_fd, buff, sizeof(buff));
                bzero(buff, sizeof(buff));
                read(this->_connection_fd, buff, sizeof(buff));
                printf("From Server : %s", buff);
                if ((strncmp(buff, "EXIT", 4)) == 0) {
                    printf("Client Exit...\n");
                    break;
                }
            }*/

            while (this->is_running) {
                //dprint("tick in buffer listener loop...");
                bzero(buff,sizeof(buff));
                if (this->hasReadableData()) {
                    read(this->_connection_fd,buff,this->hasReadableData());
                    if (strcmp(buff,"READY\e") == 0){
                        dprint("Client:\tServer is ready!");
                        this->is_server_ready = true;
                    } else {
                        dprint("Client:\tRecieved readable data!");
                        this->_read_buffer = buff;
                    }
                }
                if (this->_write_buffer.size()) {
                    if (this->_write_buffer[0].size() && this->is_server_ready){
                        dprint("Client:\tServer is ready and we have data to send!");
                        write(this->_connection_fd,this->_write_buffer[0].c_str(),sizeof(this->_write_buffer[0].c_str()));
                        this->_write_buffer.erase(this->_write_buffer.begin());
                        this->is_server_ready = false;
                    }
                }
            }

        };
        this->_threads.insert(this->_threads.begin(),std::thread(listener));
    }
    
    TCP::TCP(std::string,int){
        dprint("Constructing TCP client...");
        this->_connection_fd = this->constructConnection("127.0.0.1",1234);
        dprint("Client:\tStarting listener...");
        this->startBufferListener();
    }

    TCP::~TCP(){
        dprint("Deconstructing TCP client...");
        this->is_running = false;
        for (auto &th : this->_threads){
            if (th.joinable()){
                th.join();
            }
        }
    }

    int TCP::hasReadableData(){

        int socket_fd = this->_connection_fd;
        int bytes_available = 0;

        if (ioctl(socket_fd, FIONREAD, &bytes_available) == 0) {
            return bytes_available;
        } else {
            return -1;
        }
    }

    TCP &TCP::operator<<(std::string _input){
        this->_write_buffer.push_back(_input);
        return *this;
    }

    TCP &TCP::operator>>(std::string& _output){
        dprint("Client:\tAttempting a read of buffer data");
        _output = this->_read_buffer;
        this->_read_buffer.clear();
        return *this;
    }
}

#elif _WIN32
#endif