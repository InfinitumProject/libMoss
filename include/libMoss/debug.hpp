#pragma once
#include <iostream>
#include <string.h>

namespace Moss::Debug {
    bool debug = strcasecmp(getenv("DEBUG"),"true");

    void dprint(){
        std::cout << std::endl;
    }

    template <typename U1, typename... U2>
    void dprint(U1 _input, U2... _others){
        if (debug){
            std::cout << _input;
            dprint(_others...);
        }
    }
}
