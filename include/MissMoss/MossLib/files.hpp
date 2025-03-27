#ifdef __linux__
//Linux Code
#pragma once
#include <string>
#include <filesystem>
#include <vector>
#include <map>

namespace MissMoss{
    namespace Files{
        namespace Executable{
            /**
             * @brief Gets the absolute path of the directory the executable is in.
             */
            std::string getExe();
        }
        namespace Text{
            /**
             * @brief Reads a full file and outputs it's contents.
             * 
             * @param fileToRead A string path to the file to read; relative to the executable.
             * 
             * @return The full content of the file in one std::string. 
             */
            std::string readFullFile(std::string fileToRead);
        }
        std::map<int,char> byteCharMappings = {{0,'0'},{1,'1'},{2,'2'},{3,'3'},{4,'4'},{5,'5'},{6,'6'},{7,'7'},{8,'8'},{9,'9'},{10,'A'},{11,'B'},{12,'C'},{13,'D'},{14,'E'},{15,'F'}};
        class byte {
            int data;
            public:

            class overflowError : public std::overflow_error {
                public:
                overflowError(const std::string &message) : std::overflow_error(message) {
                    this->what();
                }
                const char *what() const noexcept override {
                    return "MissMoss::Files::bytes::byte\nError: Overflow Error on byte construction\n";
                }
            };
            
            byte();
            byte(int);
            byte(int[2]);
            byte(int,int);
            byte(std::pair<int,int>);
            operator std::string();
            operator int();
            operator char();
            byte &operator++();
            byte operator++(int);
            byte &operator--();
            byte operator--(int);
            byte &operator+(int);
            byte &operator-(int);
        };
        class bytes {
            std::vector<byte> data;
            void revalidate();
            public:
            bytes();
            bytes(byte);
            bytes(std::vector<byte>);
            operator std::string();
            byte &operator[](int);
            int size();
            class iterator {
                int position;
                bytes *_source;
                public:
                iterator(bytes&);
                iterator(bytes&, int);
                iterator(bytes*);
                iterator(bytes*, int);
                bool operator==(iterator);
                bool operator!=(iterator);
                iterator &operator++();
                iterator &operator--();
                iterator &operator++(int);
                iterator &operator--(int);
                iterator operator+(int);
                iterator operator-(int);
                byte &operator*();
            };
            bytes::iterator begin();
            bytes::iterator end();
        };
    }
}
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif