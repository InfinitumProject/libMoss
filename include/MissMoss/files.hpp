#ifdef __linux__
//Linux Code
#pragma once
#include <string>
#include <filesystem>

namespace MissMoss{
    namespace Executable{
        std::string getExe();
    }
}
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif