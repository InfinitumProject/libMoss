#ifdef __linux__
//Linux Code
#pragma once
#include <iostream>
#include <functional>
#include <vector>

namespace MissMoss {
    namespace CLI {
        class BasicCLI{
            BasicCLI(std::vector<std::pair<std::function<std::string(std::string)>*,std::string>> input);
        };
    }
}

#elif _WIN32

#endif