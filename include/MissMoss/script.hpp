#ifdef __linux__
//Linux Code
#pragma once
#include <string>
#include <vector>

namespace MissMoss{
    namespace Script{
        /**
        * @brief Splits a string by a deliminator.
        *
        * @param input The string to split.
        * @param delim The deliminator to split it by.
        * @param append_delim Whether to append the deliminator character to the end of the last string.
        */
        std::vector<std::string> tokenize(std::string input, char delim, bool append_delim);

        /**
        * @brief Splits a string by a deliminator.
        *
        * @param input The string to split.
        * @param delim The deliminator to split it by.
        * @param &output The variable to assign the result to.
        * @param append_delim Whether to append the deliminator character to the end of the last string.
        */
        void tokenize(std::string input, char delim, bool append_delim, std::vector<std::string> &output);
    }
}
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif