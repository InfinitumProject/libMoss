#ifdef __linux__
//Linux Code
#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <variant>
#include <nlohmann/json.hpp>

namespace MissMoss {

    /**
     * @brief The namespace holding everything to do with the CLI interface.
     */
    namespace CLI {

        /**
         * @brief The type of function i.e. std::string(std::string).
         */
        typedef std::function<std::string(std::string)> mapFunction;

        /**
         * @brief A class to store and handle a list of functions that act on the CLI in some way. If this seems arbitrary, that is intentional.
         */
        class commandMapping {
            public:

                /**
                 * @brief A basic constructor.
                 * @param initialMap A map to initialize the internal mappings with.
                 */
                commandMapping(std::map<std::string,mapFunction>);

                /**
                 * @brief A basic constructor.
                 */
                commandMapping();

                /**
                 * @brief An operator for appending a pair to the internal mappings.
                 * @param toAdd The pair to add.
                 * @returns A reference to itself so you can chain the calls.
                 */
                commandMapping &operator+=(std::pair<std::string,mapFunction>);

                /**
                 * @brief An operator for appending a map to the internal mappings.
                 * @param toAdd The map to append to the internal mappings.
                 * @returns A reference to itself so you can chain the calls.
                 */
                commandMapping &operator+=(std::map<std::string,mapFunction>);

                /**
                 * @brief Simply calls a stored function with the given input.
                 * @param func The function identifier to call.
                 * @param arg The argument to pass to the function
                 * @returns the output of the referenced function.
                 */
                std::string operator()(std::string,std::string);

            private:
                /**
                 * @brief The internal function mappings stored within the class.
                 */
            std::map<std::string,mapFunction> Mappings;
        };

        class BasicCLI {
            protected:
                commandMapping InternalMappings;
            private:
                bool exited;
            public:
                BasicCLI(commandMapping);
                void operator()();
                std::string commandLineBase;
                std::string commandLineEnd;
                std::function<std::string(std::string,std::string)> frameFunc;
        };
    }
}

#elif _WIN32

#endif