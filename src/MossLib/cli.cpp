#ifdef __linux__
//Linux Code

#include <iostream>
#include "../../include/MissMoss/cli.hpp"

std::string doSomething(std::string newName){
    return newName;
}

std::vector<std::pair<std::function<std::string(std::string)>*,std::string>> mappings = {{doSomething,"something"}};
MissMoss::CLI::BasicCLI e = MissMoss::CLI::BasicCLI(mappings);

#elif _WIN32

#endif