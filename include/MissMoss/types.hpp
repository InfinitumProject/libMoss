#ifdef __linux__
#pragma once
#include <vector>
#include <string>
#include <functional>
#include <stdarg.h>
#include <variant>
namespace MissMoss{
    namespace Types{
        typedef std::vector<std::variant<std::string,char*>> tokens;
        typedef std::variant<void,int,std::string,tokens> functionParams;
        typedef std::function<functionParams(tokens&)> function;
    }
}
#elif _WIN32
#endif