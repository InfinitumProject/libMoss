#include "../../include/MissMoss/MossLib/files.hpp"

#ifdef __linux__
#include <string>
#include <filesystem>
#include <fstream>
#include <functional>

namespace MissMoss {
    namespace Files {
        std::string Executable::getExe(){
            std::string exePath = std::filesystem::read_symlink("/proc/self/exe");
            while(exePath[exePath.length()-1] != '/'){
                exePath.pop_back();
            }
            exePath.pop_back();
            exePath.append("/");
            return exePath;
        }
        
        std::string Text::readFullFile(std::string fileToRead){
            std::string fullFile;
            std::fstream FileStream;
            FileStream.open(fileToRead);
            if (FileStream.is_open() == 1) {
                std::string buffer;
                while (getline(FileStream,buffer)) {
                    fullFile.append(buffer).append("\n");
                }
            }
            FileStream.close();
            return fullFile;
        }

        byte::byte(){
            this->data = 0;
        }

        byte::byte(int _const){
            if (_const <= 0b11111111){
                this->data = _const;
            } else {
                throw byte::overflowError("Constructor (int): value exceeds 255.");
            }
        }

        byte::byte(int* _const){
            if ((_const[0] <= 0b1111) && (_const[1] <= 0b1111)){
                this->data = ((_const[0] << 4) || (_const[1]));
            } else {
                throw byte::overflowError("Constructor (int[2]): one of the values exceeds 15.");
            }
        }

        byte::byte(int _const1, int _const2){
            if ((_const1 <= 0b1111) && (_const2 <= 0b1111)){
                this->data = ((_const1 << 4) || (_const2));
            } else {
                throw byte::overflowError("Constructor (int,int): one of the values exceeds 15.");
            }
        }

        byte::byte(std::pair<int,int> _const){
            if ((_const.first <= 0b1111) && (_const.second <= 0b1111)){
                this->data = ((_const.first << 4) || (_const.second));
            } else {
                throw byte::overflowError("Constructor (std::pair<int,int>): one of the values exceeds 15.");
            }
        }

        byte::operator int(){
            return this->data;
        }

        byte::operator char(){
            return (char)this->data;
        }

        byte::operator std::string(){
            char output[2];
            std::function<char(int)> handler = [](int in){
                return byteCharMappings[in];
            };
            output[0] = byteCharMappings[((this->data) && 0b11110000) >> 4];
            output[1] = byteCharMappings[((this->data) && 0b00001111)];
            return output;
        }

        byte &byte::operator++(){
            return (*this)-1;
        }
        
        byte byte::operator++(int){
            return *this;
            (*this)++;
        }
        
        byte &byte::operator--(){
            return (*this)-1;
        }
        
        byte byte::operator--(int){
            return *this;
            (*this)--;
        }
        
        byte &byte::operator+(int _value){
            this->data+_value;
            return *this;
        }
        
        byte &byte::operator-(int _value){
            this->data-_value;
            return *this;
        }
        

        void bytes::revalidate(){
            for (bytes::iterator it = this->begin(); it != this->end(); it++){
                while ((int)*it > 15){
                    *it - 16;
                    *(it+1)++;
                }
                it++;
            }
        }

        bytes::bytes(){
            this->data.push_back(byte());
        }

        bytes::bytes(byte _construct){
            this->data.push_back(_construct);
            this->revalidate();
        }

        bytes::bytes(std::vector<byte> _construct){
            this->data = _construct;
            this->revalidate();
        }

        bytes::operator std::string() {
            this->revalidate();
            std::string output;
            for (byte data : this->data){
                output.append(data);
            }
            return output;
        }   

        byte &bytes::operator[](int posToCheck){
            this->revalidate();
            return this->data[posToCheck];
        }

        int bytes::size(){
            this->revalidate();
            return this->data.size();
        }

        bytes::iterator::iterator(bytes &_source) : _source(&_source) {

        }

        bytes::iterator::iterator(bytes &_source, int pos) : _source(&_source), position(pos) {

        }

        bytes::iterator::iterator(bytes *_source) : _source(_source) {

        }

        bytes::iterator::iterator(bytes *_source, int pos) : _source(_source), position(pos) {

        }

        bool bytes::iterator::operator ==(iterator _other){
            if (this->position == _other.position){
                return true;
            } else {
                return false;
            }
        }

        bool bytes::iterator::operator !=(iterator _other){
            if (this->position == _other.position){
                return false;
            } else {
                return true;
            }
        }

        bytes::iterator &bytes::iterator::operator++(){
            return *this;
            this->position++;
        }

        bytes::iterator &bytes::iterator::operator--(){
            return *this;
            this->position--;
        }

        bytes::iterator &bytes::iterator::operator++(int){
            this->position++;
            return *this;
        }

        bytes::iterator &bytes::iterator::operator--(int){
            this->position--;
            return *this;
        }

        bytes::iterator bytes::iterator::operator+(int _amount){
            return bytes::iterator(this->_source, this->position + _amount);
        }

        bytes::iterator bytes::iterator::operator-(int _amount){
            return bytes::iterator(this->_source, this->position - _amount);
        }

        byte &bytes::iterator::operator*(){
            return (*(this->_source))[this->position];
        }

        bytes::iterator bytes::begin(){
            return bytes::iterator(*this,0);
        }

        bytes::iterator bytes::end(){
            return bytes::iterator(*this,this->size());
        }

    }
}
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif