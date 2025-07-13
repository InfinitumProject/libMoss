#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <any>

namespace MissMoss::CLI {

    namespace Exceptions
    {
        class any_cast_failure : public std::exception {
        public:
            explicit any_cast_failure(const std::string& message) : errorMessage(message) {}
            
            const char* what() const noexcept override {
                return errorMessage.c_str();
            }
        private:
            std::string errorMessage;
        };
    }
    

    /**
     * @brief A class to hold mappings of functions and sub data
     * structures a flexible framework for command interactions.
     */
    struct Data {
        private:
            /**
             * @brief The variable that holds the main data block
             */
            std::map<std::string,std::any> internalData;
        public:
            /**
             * @brief A basic constructor.
             */
            Data();

            /**
             * @brief The lookup operator is intended to be used inside
             * of a loop, iterating over the command to find the path to the
             * actual function to be run.
             */
            auto &operator[](std::string);

            /**
             * @brief Used to add an entry to the current data block,
             * adds a sub-entry.
             * @param key The key used to access the data sub-block.
             * @param data The data sub-block to access.
             */
            Data &add(std::pair<std::string,Data>);

            /**
             * @brief Used to add an entry to the current data block,
             * adds a function executor.
             * @param key The key used to access the function executor. 
             * @param function The function to execute when reached. \n
             * (Following arguments will be captured and passed as a 
             * single string, it is up to you to parse them.)
             */
            Data &add(std::string,std::function<void(std::string)>);
    };

    /**
     * @brief The actual CLI interface, used to interface in a way that
     * feels good in a terminal.
     */
    class CLI {
        public:
            /**
             * @brief A basic constructor.
             * @param Data The mapping of data and functions.
             */
            CLI(Data);

    };
}