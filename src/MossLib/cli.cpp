#include "../../include/MissMoss/cli.hpp"

#ifdef __linux__
#include <iostream>
#include <thread>
#include <chrono>

namespace MissMoss {
    namespace CLI {
        commandMapping::commandMapping(std::map<std::string,mapFunction> initMap) : Mappings(initMap) {}
        commandMapping::commandMapping(){}
        commandMapping &commandMapping::operator+=(std::pair<std::string, mapFunction> toAdd){
            Mappings[toAdd.first] = toAdd.second;
            return *this;
        }
        commandMapping &commandMapping::operator+=(std::map<std::string, mapFunction> toAdd){
            Mappings.merge(toAdd);
            return *this;
        }
        std::string commandMapping::operator()(std::string func,std::string input){
            return std::string(Mappings[func](input));
        }

        BasicCLI::BasicCLI(commandMapping initMappings) : InternalMappings(initMappings){}
        void BasicCLI::operator()(){
            while (!exited){
                frameFunc(commandLineBase,commandLineEnd);
            }
        }
    }
}
    

#elif _WIN32

#endif