#ifdef __linux__

#include <iostream>
#include "../../include/MissMoss/cli.hpp"

std::string doSomething(std::string newName){
    return newName;
}

MissMoss::CLI::BasicCLI::BasicCLI(){
}
MissMoss::CLI::BasicCLI::BasicCLI(nlohmann::json mappingsToSet){
    mappings = mappingsToSet;
}
int MissMoss::CLI::BasicCLI::operator()(std::string entrypointPath[]){
    nlohmann::json mappingExplorer = mappings;
    int entrypointPathIndex = 0;
    while (mappingExplorer["Endpoint"] != true){
        mappingExplorer = mappingExplorer[entrypointPath[entrypointPathIndex]];
        entrypointPathIndex++;
        if (entrypointPathIndex >= entrypointPath->length()){
            throw new MissMoss::CLI::BasicCLI::invalidPathException;
        }
    }
}

#elif _WIN32

#endif