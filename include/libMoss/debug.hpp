#pragma once
#include <iostream>
#include <string.h>

namespace Moss::Debug {    
    void dprint(const char *_input, bool _newline = true, const char *_print_if = "DEBUG"){
        const char *val = getenv(_print_if);
        bool is_true = (strcmp(val,"true") == 0) || (strcmp(val,"True") == 0);
        if (is_true){
            std::cout << _input;
            if (_newline){
                std::cout << std::endl;
            }
        }
    }

    void dprint(int _input, bool _newline = true, const char *_print_if = "DEBUG"){
        const char *val = getenv(_print_if);
        bool is_true = (strcmp(val,"true") == 0) || (strcmp(val,"True") == 0);
        if (is_true){
            std::cout << _input;
            if (_newline){
                std::cout << std::endl;
            }
        }
    }
}
