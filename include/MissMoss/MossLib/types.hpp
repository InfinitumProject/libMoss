#ifdef __linux__
#pragma once
#include <vector>
#include <string>
#include <functional>
#include <stdarg.h>
#include <variant>
namespace MissMoss{
    namespace Types{
        typedef std::vector<std::string> tokens;
        typedef std::function<std::string(std::vector<std::string>)> function;
    }
}
#elif _WIN32
#endif