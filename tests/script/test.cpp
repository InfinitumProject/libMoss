#include "../../include/MissMoss/MossLib/script.hpp"
#include "../../include/MissMoss/MossLib/files.hpp"
#include "../../include/MissMoss/MossLib/types.hpp"
#include <iostream>

MissMoss::Types::tokens stringReplaceTest(MissMoss::Types::tokens input, std::map<char,char> replace){
    MissMoss::Types::tokens output = input;
    for (std::string str : output){
        for (std::pair<char,char> pair : replace){
            std::string temp("\\");
            temp.push_back(pair.first);
            int pos = str.find(temp);
            while (pos != std::string::npos){
                std::cout << "found \\n at position: " << pos << std::endl;
                str[pos] = '\n';
                str.erase(pos+1,1);
                pos = str.find(temp);
            }
        }
    }
    return output;
}

int main(int argc, char *argv[]){
    MissMoss::Script::ScriptProcessor scripter;
    scripter.registerFunction("print",[](MissMoss::Types::ioVarianceVector _inputs){for (MissMoss::Types::ioVarianceSinglet a : _inputs){std::cout<<a;} return 0;});
    scripter.ProcessLine(MissMoss::Files::Text::readFullFile(argv[1]));
    for (std::string str : stringReplaceTest(std::vector<std::string>({"This is a newline test.\\n","This concludes the newline test."}),{{'n','\n'}})){
        std::cout << str;
    }
    std::vector<std::string> a = {"000\\x00\\x0","0\\x00\\x00\\x"};
    for (std::string str : a){
        int pos = str.find('\\');
        while (pos != std::string::npos){
            str[pos] = '1';
            str.erase(pos+1,1);
            pos = str.find('\\');
        }
        std::cout << str << std::endl;
    }

    for (std::string str : stringReplaceTest({"000\\x00\\x0","0\\x00\\x00\\x"},{{'x','1'}})){
        std::cout << str << std::endl;
    }
}