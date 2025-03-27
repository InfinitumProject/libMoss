#include "../../include/MissMoss/MossLib/files.hpp"

#ifdef __linux__
#include <string>
#include <filesystem>
#include <fstream>

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

        void bytes::revalidate(){
            for (bytes::iterator it = this->begin(); it != this->end(); it++){
                while (*it > 15){
                    *it - 16;
                    *(it+1)++;
                }
                it++;
            }
        }

        bytes::bytes(){

        }

        bytes::bytes(int _construct){
            this->data.push_back(_construct);
            this->revalidate();
        }

        bytes::bytes(std::vector<int> _construct){
            this->data = _construct;
            this->revalidate();
        }

        bytes::bytes(std::vector<char> _construct){
            for (char data : _construct){
                this->data.push_back(data);
            }
            this->revalidate();
        }

        std::string bytes::to_string(){
            this->revalidate();
            std::string output;
            for (int data : this->data){
                switch (data)
                {
                    case 0:
                    output.append("0");
                    break;
                    case 1:
                    output.append("1");
                    break;
                    case 2:
                    output.append("2");
                    break;
                    case 3:
                    output.append("3");
                    break;
                    case 4:
                    output.append("4");
                    break;
                    case 5:
                    output.append("5");
                    break;
                    case 6:
                    output.append("6");
                    break;
                    case 7:
                    output.append("7");
                    break;
                    case 8:
                    output.append("8");
                    break;
                    case 9:
                    output.append("9");
                    break;
                    case 10:
                    output.append("A");
                    break;
                    case 11:
                    output.append("B");
                    break;
                    case 12:
                    output.append("C");
                    break;
                    case 13:
                    output.append("D");
                    break;
                    case 14:
                    output.append("E");
                    break;
                    case 15:
                    output.append("F");
                    break;
                default:
                    break;
                }
            }
        }

        bytes::operator char*(){
            this->revalidate();
            char *returnVal;
            for (char ch : std::string(*this)){
                returnVal[sizeof(returnVal)] = ch;
            }
            return returnVal;
        }

        int &bytes::operator[](int posToCheck){
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

        int &bytes::iterator::operator*(){
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