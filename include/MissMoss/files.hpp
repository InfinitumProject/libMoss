#ifdef __linux__
//Linux Code
#pragma once
#include <string>
#include <filesystem>

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
    }
}
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif