#ifdef __linux__
//Linux Code
#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include "../Nlohmann/json.hpp"

namespace MissMoss {
    namespace CLI {
        class BasicCLI{
            BasicCLI();
            BasicCLI(nlohmann::json mappingsToSet);
            nlohmann::json mappings;
            int operator()(std::string entrypointPath[]);
            class invalidPathException : std::exception{
                public:
                    const char* what() const noexcept override {
                        return "Invalid path entrypoint provided!!";
                    }
            };
        };
    }
}

#elif _WIN32

#endif