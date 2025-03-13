#include "MissMoss/cli.hpp"
#ifdef __linux__

MissMoss::CLI::mapFunction func([](std::string a){return a;});

MissMoss::CLI::commandMapping cli_mappings({{std::string("echo"),func}});

MissMoss::CLI::BasicCLI __cli(cli_mappings);
__cli;

#elif _WIN32
#endif