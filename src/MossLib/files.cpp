#ifdef __linux__
#include <string>
#include <filesystem>
#include <fstream>
#include "../../include/MissMoss/files.hpp"

std::string MissMoss::Files::Executable::getExe(){
    std::string exePath = std::filesystem::read_symlink("/proc/self/exe");
    while(exePath[exePath.length()-1] != '/'){
        exePath.pop_back();
    }
    exePath.pop_back();
    exePath.append("/");
    return exePath;
}
std::string MissMoss::Files::Text::readFullFile(std::string fileToRead){
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
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif