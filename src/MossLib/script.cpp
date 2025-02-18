#ifdef __linux__
#include <string>
#include <filesystem>
#include <fstream>
#include "../../include/MissMoss/script.hpp"

std::vector<std::string> MissMoss::Script::tokenize(std::string input, char delim, bool append_delim){
    std::vector<std::string> output;
    int last = 0, current;
    for (int i = 0; i < input.length(); i++){
        if (input[i] == '\n'){
            current = i;
            output.push_back(input.substr(last, current - last));
            //split_file.append(file.substr(last, current - last));
            last = i;
        }
    }
    if (append_delim) {
        output.back() += delim;
    }
    return output;
}

void MissMoss::Script::tokenize(std::string input, char delim, bool append_delim, std::vector<std::string> &output){
    int last = 0, current;
    for (int i = 0; i < input.length(); i++){
        if (input[i] == '\n'){
            current = i;
            output.push_back(input.substr(last, current - last));
            last = i;
        }
    }
    if (append_delim) {
        output.back() += delim;
    }
    output.back() += delim;
}

#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif