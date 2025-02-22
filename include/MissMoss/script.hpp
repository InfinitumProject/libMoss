#ifdef __linux__
//Linux Code
#pragma once
#include "types.hpp"
#include <string>
#include <vector>
#include <map>
#include <string.h>
#include <iostream>
#include <functional>

namespace MissMoss{
    namespace Script{
        /**
        * @brief Splits a string by a deliminator.
        *
        * @param input The string to split.
        * @param delim The deliminator to split it by.
        * @param append_delim Whether to append the deliminator character to the end of the last string.
        */
        tokens tokenize(std::string input, char delim, bool append_delim);

        /**
        * @brief Splits a string by a deliminator.
        *
        * @param input The string to split.
        * @param delim The deliminator to split it by.
        * @param append_delim Whether to append the deliminator character to the end of the last string.
        * @param &output The variable to assign the result to.
        */
        void tokenize(std::string input, char delim, bool append_delim, tokens &output);

        /**
        * @brief Splits a string by multiple deliminators.
        *
        * @param input The string to split.
        * @param delim A vector of deliminators to split it by.
        */
        tokens multiTokenize(std::string input, std::vector<char> delim);

        /**
        * @brief Splits a string by a deliminator.
        *
        * @param input The string to split.
        * @param delim A vector of deliminators to split it by.
        * @param &output The variable to assign the result to.
        */
        void multiTokenize(std::string input, std::vector<char> delim, tokens &output);

        /**
         * @brief Used to clump strings back into a singular token.
         * 
         * @param inputs A vector of tokens to attempt to restring.
         */
        tokens restringTokens(tokens &inputs);

        /**
         * @brief Used to clump strings back into a singular token.
         * 
         * @param inputs A vector of tokens to attempt to restring.
         * @param output A vector to output the function to.
         */
        void restringTokens(tokens &inputs, tokens &output);
        
        /**
         * @brief Runs through a map and outputs the keys.
         * @brief Uses templating so you need to construct it with typenames too.
         * 
         * @param input A map to run through
         * @returns A vector of keys. 
         */
        template <typename T1,typename T2>
        std::vector<T1> getMapKeys(std::map<T1,T2> &input);

        /**
         * @brief Constructs an instance of the script processor.
         * 
         * @param exposedVariables A map of the exposed variables as well as pointers to their data.
         */
        class ScriptProcessor{
            public:
                /**
                 * @brief Constructs an instance of the script processor.
                 */
                ScriptProcessor();
                /**
                 * @brief Processes a single line of script. Pretty self explanatory.Script
                 * 
                 * @param lineToProcess A string containing a line from a script.
                 */
                int ProcessLine(std::string lineToProcess);
                /**
                 * @brief Processes multiple lines of script organized in a vector in order of application.
                 * 
                 * @param linesToProcess A vecor containing strings to process.
                 */
                int ProcessLines(tokens linesToProcess);
                /**
                 * @brief Takes a pair of settings and attempts to change a setting.
                 * 
                 * @param setting A pair of strings, the first being the setting and the second being the value.
                 */
                void setSetting(std::pair<std::string,std::string> setting);
                /**
                 * @brief Dumps the current settings into the given string or iosstream.
                 * 
                 * @param stream The stream to dump the settings to. 
                 * @param end The string to dump to the stream after the settings; "\\n" by default.
                 */
                void dumpSettings(std::ostream &stream, const char *end = "\n");
                /**
                 * @brief Dumps the current settings into the given string or iosstream.
                 * 
                 * @param string The string to dump the settings to. 
                 */
                void dumpSettings(std::string &string);
                /**
                 * @brief Used to register a function to the standard library.Script
                 * 
                 * @param alias The text used to call the function in the script.
                 * @param functionRef A function reference to be called.
                 */
                void registerFunction(std::string alias, std::function<int(void*)> functionRef);
            protected:
                /**
                 * @brief Contains the exceptions that are used for error handling here. Pretty standard stuff.
                 */
                struct Exceptions{
                    /*class AssignSettingFail : public std::exception{
                        public:
                            const char *terminateMessage;
                            AssignSettingFail(std::pair<std::string,std::string> failedPair){
                                std::string output = std::string("Failed to assign setting \"") + failedPair.first + std::string("\" to value \"") + failedPair.second + std::string("\"!!");
                                int len = output.length()+1;
                                char *buff = new char[len];
                                strcpy(buff,output.c_str());
                                this->terminateMessage = buff;
                            }
                            const char* what() const noexcept override {
                                return terminateMessage;
                            }
                    };*/
                };
                /**
                 * @brief Holds a map of exposed variable names and pointers to their values
                 */
                std::map<std::string,void*> exposedVariables;

                /**
                 * @brief Holds the script level which tweaks the level of the scripting system.
                 */
                int level;

                /**
                 * @brief Holds data for settings in a map.
                 */
                std::map<std::string,std::string> settings;

                /**
                 * @brief Holds mappings for functions, though all functions will only be able to
                 * @brief take a pointer to data as an input and return an int. I'll work on fixing that.
                 */
                std::map<std::string,std::function<int(void*)>> functionMappings;

                /**
                 * @brief Holds deliminators to split scripts by, you probably don't 
                 * @brief wanna change this unless you really know what you're doing.
                 */
                std::vector<char> delims;
        };
    }
}
#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif