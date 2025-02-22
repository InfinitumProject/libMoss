#include "../../include/MissMoss/script.hpp"
#include "../../include/MissMoss/files.hpp"
#include <iostream>

int print(void *input){
    std::cout << input << std::endl;
    return 1;
}

int main(int argc, char *argv[]){
    MissMoss::Script::ScriptProcessor scripter({});
    scripter.setSetting({"setting1","value1"});
    scripter.setSetting({"setting1","value2"});
    scripter.dumpSettings(std::cout);
    for (std::string str : MissMoss::Script::tokenize(MissMoss::Files::Text::readFullFile(argv[1]),'\n',1)){
        std::cout << str << std::endl;
    }

    std::cout << "Now splitting by multiple characters!!!" << std::endl;

    for (std::string str : MissMoss::Script::multiTokenize(MissMoss::Files::Text::readFullFile(argv[1]),{';','(',')',',','"',' '})){
        std::cout << "found: \"" << str << "\"" << std::endl;
    }

    std::cout << "attempting to restring tokens..." << std::endl;
    tokens tok = MissMoss::Script::multiTokenize(MissMoss::Files::Text::readFullFile(argv[1]),{';','(',')',',','"',' '});
    for (std::string str : MissMoss::Script::restringTokens(tok)){
        std::cout << str << std::endl;        
    }
    std::function<int(void*)> print2 = print;
    scripter.registerFunction("print",print);
}