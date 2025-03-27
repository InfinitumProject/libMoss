#ifdef __linux__
//Linux Code
#pragma once
#include <string>
#include <filesystem>
#include <vector>

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
        class bytes {
            std::vector<int> data;
            void revalidate();
            public:
            bytes();
            bytes(int);
            bytes(std::vector<int>);
            bytes(std::vector<char>);
            operator std::vector<int>();
            std::string to_string();
            operator char*();
            int &operator[](int);
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
                int &operator*();
            };
            bytes::iterator begin();
            bytes::iterator end();
        };
    }
}
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif