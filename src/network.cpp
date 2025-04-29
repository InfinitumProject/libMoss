#include "../include/libMoss/network.hpp"
#include "../include/libMoss/debug.hpp"
#define WAIT_SECS 2.5

#ifdef __linux

#include <sys/ioctl.h>

namespace Moss::Network {

    int TCP::constructConnection(std::string _address, int _port, int _connection_retries){
        int sockfd;
        struct sockaddr_in servaddr;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            throw new socketError::socketCreationError;
        }
        else {
            dprint("Connection Constructor:\tSocket successfully created..");
        }
        dprint("Connection Constructor:\tDoing bzero for server address...");
        bzero(&servaddr, sizeof(servaddr));

        dprint("Connection Constructor:\tConfiguring server address...");
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(_address.c_str());
        servaddr.sin_port = htons(_port);

        dprint("Connection Constructor:\tAttempting Connection...");
        int conn_try;
        for (int n = 0; n < _connection_retries; n++){
            conn_try = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
            if (conn_try != 0) {
                dprint("Connection Constructor:\tConnected to the server...");
                return sockfd;
            }
            dprint("Connection Constructor:\tFailed: Awaiting another try...");
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(2.5s);
        }
        throw new socketError::socketConnectionError;
    }

    void TCP::startBufferListener(){
        dprint("Client:\tDefining lambda listener function...");
        auto listener = [&](){
            dprint("Client:\tHello from listener thread!");
            char buff[65535];

            while (this->is_running) {
                bzero(buff,sizeof(buff));
                if (this->hasReadableData()) {
                    read(this->_connection_fd,buff,this->hasReadableData());
                    if (strcmp(buff,READY_PACKET) == 0){
                        dprint("Client:\tServer is ready!");
                        this->is_server_ready = true;
                    } else {
                        dprint("Client:\tRecieved readable data: ", false);
                        dprint(buff);
                        this->_read_buffer = buff;
                    }
                }
                if (this->_write_buffer.size()) {
                    if (this->_write_buffer[0].size() && this->is_server_ready){
                        dprint("Client:\tServer is ready and we have data to send!");
                        dprint("Client:\tsizeof(Data): ", false);
                        dprint(std::to_string(this->_write_buffer[0].size()).c_str());
                        write(this->_connection_fd,this->_write_buffer[0].c_str(),this->_write_buffer[0].size()+1);
                        this->_write_buffer.erase(this->_write_buffer.begin());
                        this->is_server_ready = false;
                    }
                }
            }

        };
        dprint("Client:\tInserting listener thread into threadpool...");
        this->_threads.insert(this->_threads.begin(),std::thread(listener));
    }
    
    TCP::TCP(std::string _address, int _port){
        dprint("Constructing TCP client...");
        this->_connection_fd = this->constructConnection(_address.c_str(), _port, 5);
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
        dprint("Client:\tAwaiting buffer to fill for a read");
        while (!this->_read_buffer.size());
        dprint("Client:\tAttempting a read of buffer data");
        _output = this->_read_buffer;
        this->_read_buffer.clear();
        return *this;
    }
}

#elif _WIN32
#endif