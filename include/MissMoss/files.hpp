#ifdef __linux__
//Linux Code
#pragma once
#include <string>
#include <filesystem>

namespace MissMoss{
    namespace Files{
        namespace Executable{
            std::string getExe();
        }
        namespace Text{
            std::string readFullFile(std::string fileToRead);
        }
    }
}
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif