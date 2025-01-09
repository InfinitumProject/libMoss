#ifdef __linux__
#include <string>
#include <filesystem>
#include "../../include/MissMoss/files.hpp"

std::string MissMoss::Executable::getExe(){
    std::string exePath = std::filesystem::read_symlink("/proc/self/exe");
    while(exePath[exePath.length()-1] != '/'){
        exePath.pop_back();
    }
    exePath.pop_back();
    exePath.append("/");
    return exePath;
}
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif