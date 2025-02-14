#include "./include/MissMoss/files.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include <vector>

std::vector<std::string> tokenize(std::string input, char delim){
    std::cout << "Test" << std::endl;
    std::cout << input << std::endl;
    std::vector<std::string> output;
    std::stringstream stream(input);
    std::string buffer;
    int i = 0;
    while (getline(stream,buffer,delim)){
        output[i] = buffer;
        i++;
        std::cout << buffer << std::endl;
    }
    return output;
}

/*void tokenize_exa(std::string s, std::string del = " "){
    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = s.find(del, start);
        std::cout << s.substr(start, end - start) << std::endl;
    } while (end != -1);
}*/

using namespace std::chrono_literals;

int main(int argc, char *argv[]){
    std::string test = MissMoss::Files::Text::readFullFile(std::string(argv[1]));
    std::cout << test << std::endl;
    //std::this_thread::sleep_for(2.5s);
    
    tokenize(test,'\n');
    
    for (int a : (int[]){1,2,3,4}){
        std::this_thread::sleep_for(1s);
        std::cout << a << std::endl;
    }
}