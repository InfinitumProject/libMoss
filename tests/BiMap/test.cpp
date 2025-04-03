#include "../../include/MossLib/DataHandler.hpp"
#include "../../src/DataHandler.cpp"
#include <iostream>

int main(){
    try {

        //test with string and char
        Moss::Data::bimap<std::string,char> test1;
        test1.append({"test",'h'});
        test1["test"];
        test1['h'];
        
        //test with int and float
        Moss::Data::bimap<int,float> test2;
        test2.append({0,0.12345});
        test2[0];
        test2[(float)0.12345];

        //testing bimap in a (range-based) for loop
        Moss::Data::bimap<std::string,const char *> test3;
        test3.append({{"Hello","world"},{"how","are"},{"you","?"}});

        std::string toCheck;
        for (std::pair<std::string,const char *> pair : test3) {
            toCheck.append(pair.first).append(" ").append(pair.second).append(" ");
        }
        if (toCheck != "Hello world how are you ? "){
            //throw std::exception();
        }

        //testing bimap in a (traditional) for loop
        Moss::Data::bimap<std::string,const char *> test4 = test3;
        toCheck.clear();
        for (Moss::Data::bimap<std::string,const char *>::iterator it = test4.begin(); it != test4.end(); it++) {
            if ((*it).second != "?") {
                toCheck.append((*it).first += " ").append((*it).second).append(" ");
            } else {
                toCheck.append((*it).first).append((*it).second);
            }
        }
        if (toCheck != "Hello world how are you?") {
            throw std::exception();
        }

        //This is all bimap tests completed.

        return 0;

    } catch (...) {
        return -1;
    }
}