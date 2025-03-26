#ifdef __linux__
#pragma once
#include <vector>
#include <string>
#include <functional>
#include <stdarg.h>
#include <variant>
namespace MissMoss{
    namespace Types{
        typedef std::variant<char,void,void*,int,char*,std::string,float> ioVarianceSinglet;
        typedef std::vector<ioVarianceSinglet> ioVarianceVector;
        typedef std::vector<std::string> tokens;
        typedef std::function<std::string(std::vector<std::string>)> function;
        class ioVarianceVisitor {
            void operator()(void){}
            auto operator()(char arg){return arg;}
            auto operator()(void* arg){return arg;}
            auto operator()(int arg){return arg;}
            auto operator()(char* arg){return arg;}
            auto operator()(std::string arg){return arg;}
            auto operator()(float arg){return arg;}
        };
    }
}
#elif _WIN32
#endif