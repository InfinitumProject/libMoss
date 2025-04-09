#include "../include/MossLib/network.hpp"

namespace Moss::Network {

    TCP::TCP(std::string _addr, int _port, int retryCount, std::chrono::milliseconds retryTime) : retryCount(retryCount), retryTime(retryTime) {
        if ((this->_socket = socket(AF_INET,SOCK_STREAM,0)) < 0){
            throw Moss::Network::TCP::socketError(1);
        }
        this->server_addr.sin_family = AF_INET;
        this->server_addr.sin_port = htons(_port);

        if (inet_pton(AF_INET, "127.0.0.1", &this->server_addr.sin_addr) <= 0) {
            throw Moss::Network::TCP::socketError(2);
        }

        int connected = 0;

        int i = 0;
        while ((i < this->retryCount) && (!connected)) {
            if (connect(this->_socket, (struct sockaddr*)&this->server_addr, sizeof(this->server_addr)) > -1) {
                connected = 1;
            }
            std::this_thread::sleep_for(this->retryTime);
        }
        if (!connected) {
            throw Moss::Network::TCP::socketError(3);
        }
    }

    TCP::~TCP(){}

    std::string TCP::r(){
        std::string output;

        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(this->_socket, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        int ready = 0;
        while(true){
            ready = select(this->_socket + 1, &read_fds, nullptr, nullptr, &timeout);
            if (ready > 0){
                if (FD_ISSET(this->_socket, &read_fds)){
                    char temp[65535];
                    recv(this->_socket,temp,65535,0);
                    output.append(temp);
                    break;
                }
            } else if (ready == 0){
                //Literally do nothing
            } else {
                throw socketError();
            }
        }

        return output;

        /*std::string _recieve;
        char temp[65535];
        while (read(this->_socket, temp, 65535) != 0){
            if (temp[sizeof(temp)-1] != EOF){
                _recieve.append(temp);
            }
        }
        return _recieve;*/
    }

    void TCP::w(std::string _send){
        send(this->_socket, _send.c_str(), strlen(_send.c_str()), 0);
    }

    TCP &TCP::operator<<(std::string &_send){
        w(_send);
        return *this;
    }

    TCP &TCP::operator<<(char _send[]){
        w(_send);
        return *this;
    }

    TCP &TCP::operator<<(const char _send[]){
        w(_send);
        return *this;
    }
    
    TCP &TCP::operator>>(std::string &_recieve){
        _recieve = this->r();
        return *this;
    }

    void TCP::closeConnection(){
        close(this->_socket);
    }
}