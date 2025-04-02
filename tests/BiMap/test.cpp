#include "../../include/MossLib/DataHandler.hpp"
#include "../../src/DataHandler.cpp"
#include <iostream>

int main(){
    try {

        Moss::Data::BiMap<std::string,char> test1;
        test1.append({"test",'h'});
        test1["test"];
        test1['h'];
        
        Moss::Data::BiMap<int,float> test2;
        test2.append({0,0.12345});
        test2[0];
        test2[(float)0.12345];

        return 0;

    } catch (...) {
        return -1;
    }
}