#include "../../include/MissMoss/script.hpp"
#include "../../include/MissMoss/files.hpp"
#include <iostream>

int main(int argc, char *argv[]){
    for (std::string str : MissMoss::Script::tokenize(MissMoss::Files::Text::readFullFile(argv[1]),'\n',true)){
        std::cout << str;
    }
}