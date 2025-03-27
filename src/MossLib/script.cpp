#include "../../include/MissMoss/MossLib/script.hpp"
#include "../../include/MissMoss/MossLib/types.hpp"

#ifdef __linux__
#include <string>
#include <filesystem>
#include <fstream>

namespace MissMoss::Script {
    MissMoss::Types::tokens tokenize(std::string input, char delim, bool append_delim){
        MissMoss::Types::tokens output;
        int last = 0, current;
        for (int i = 0; i <= input.length(); i++){
            if (input[i] == delim){
                current = i;
                output.push_back(input.substr(last, current - last));
                last = i;
            }
        }
        if (append_delim) {
            output.back() += delim;
        }
        return output;
    }

    void tokenize(std::string input, char delim, bool append_delim, MissMoss::Types::tokens &output){
        int last = 0, current;
        for (int i = 0; i <= input.length(); i++){
            if (input[i] == delim){
                current = i;
                output.push_back(input.substr(last, current - last));
                last = i;
            }
        }
        if (append_delim) {
            output.back() += delim;
        }
        output.back() += delim;
    }

    MissMoss::Types::tokens multiTokenize(std::string input, std::vector<char> delim){
        MissMoss::Types::tokens output;
        int last = 0, current;
        for (int i = 0; i <= input.length(); i++){
            for (char del : delim){
                if (input[i] == del){
                    current = i;
                    output.push_back(input.substr(last, current - last));
                    last = i;
                }
            }
        }
        //return processEscapes(restringTokens(output),(std::map<char,char>){{'n','\n'},{'t','\t'}});
        return restringTokens(output);
    }

    void multiTokenize(std::string input, std::vector<char> delim, MissMoss::Types::tokens &output){
        MissMoss::Types::tokens outputBuffer;
        int last = 0, current;
        for (int i = 0; i <= input.length(); i++){
            for (char del : delim){
                if (input[i] == del){
                    current = i;
                    outputBuffer.push_back(input.substr(last, current - last));
                    last = i;
                }
            }
        }
        //processEscapes(restringTokens(outputBuffer),(std::map<char,char>){{'n','\n'},{'t','\t'}},output);
        restringTokens(outputBuffer,output);
    }

    MissMoss::Types::tokens restringTokens(MissMoss::Types::tokens &_tokens){
        MissMoss::Types::tokens output;
        bool isInQuotes = false;
        std::string buffer;
        for (int i = 0; i < _tokens.size(); i++){
            if (_tokens[i][0] == '"'){
                if (isInQuotes){
                    isInQuotes = false;
                    buffer.append(_tokens[i]);
                    output.push_back(buffer.substr(1,buffer.length()-2));
                    buffer.clear();
                } else {
                    isInQuotes = true;
                    buffer.append(_tokens[i]);
                }
            } else if ((_tokens[i][0] != '"') && (!isInQuotes)) {
                output.push_back(_tokens[i]);
            } else if ((_tokens[i][0] != '"') && (isInQuotes)) {
                buffer.append(_tokens[i]);
            }
        }
        return output;
    }

    void restringTokens(MissMoss::Types::tokens &_tokens, MissMoss::Types::tokens &output){
        bool isInQuotes = false;
        std::string buffer;
        for (int i = 0; i < _tokens.size(); i++){
            if (_tokens[i][0] == '"'){
                if (isInQuotes){
                    isInQuotes = false;
                    buffer.append(_tokens[i]);
                    output.push_back(buffer.substr(1,buffer.length()-2));
                    buffer.clear();
                } else {
                    isInQuotes = true;
                    buffer.append(_tokens[i]);
                }
            } else if ((_tokens[i][0] != '"') && (!isInQuotes)) {
                output.push_back(_tokens[i]);
            } else if ((_tokens[i][0] != '"') && (isInQuotes)) {
                buffer.append(_tokens[i]);
            }
        }
    }

    template <typename U1,typename U2>
    std::vector<U1> getMapKeys(std::map<U1,U2> &input){
        std::vector<U1> keys;
        for (auto it = input.begin(); it != input.end(); ++it){
            // Add the key to the vector
            keys.push_back(it->first);
        }
        return keys;
    }

    template <typename U>
    auto vectorContentCheck(std::vector<U> &vector, U value){
        for (auto it = vector.begin(); it != vector.end(); it++){
            if (it == value){
                return it;
            } else {
                return NULL;
            }
        }
    }

    Types::tokens processEscapes(Types::tokens inputs, std::map<char,char> escapeMappings){
        for (std::string str : inputs){
            for (int i = 0; i < str.length(); i++){
                if (str[i] == '\\'){
                    i = escapeMappings[str[i]];
                    str.erase(i+1,1);
                }
            }
        }
        return inputs;
    }

    void processEscapes(Types::tokens inputs, std::map<char,char> escapeMappings, Types::tokens &output){
        for (std::string str : inputs){
            for (int i = 0; i < str.length(); i++){
                if (str[i] == '\\'){
                    i = escapeMappings[str[i]];
                    str.erase(i+1,1);
                }
            }
        }
        output = inputs;
    }
}

MissMoss::Script::ScriptProcessor::ScriptProcessor(){
    this->delims = {';','(',')',',','"',' ','{','}','[',']','\''/*,'\n'*/};
}
void MissMoss::Script::ScriptProcessor::ProcessLine(std::string lineToProcess){
    std::cout << "Running preprocessor check..." << std::endl;
    if (lineToProcess[0] == '#'){
        std::cout << "Found preprocessor line: " << lineToProcess << std::endl;
        std::string buffer = (lineToProcess.substr(1));
        std::pair<std::string,std::string> settingData({tokenize(buffer,' ',false)[0],tokenize(buffer,' ',false)[1]});
        this->setSetting(settingData);
        //delete settingData;
        //delete buffer;
    } else {
        std::cout << "Found script line, processing now..." << std::endl;
        MissMoss::Types::tokens tokenizedLine;
        std::cout << "Attempting multitokenization now..." << std::endl;
        multiTokenize(lineToProcess,this->delims,tokenizedLine);
        std::cout << "Iterating through tokens now..." << std::endl;
        for (auto it = tokenizedLine.begin(); it != tokenizedLine.end(); it++){
            std::cout << "Processing token: " << *it << std::endl;
            if (*it == "("){
                MissMoss::Types::tokens _args;
                int i = 1;
                while (*(it+i) != ")"){
                    if (*(it+i) != ","){
                        _args.push_back(*(it+i));
                    }
                    i++;
                    if (*(it+i) == "\n"){
                        std::cout << "Newline found..." << std::endl;
                    }
                }
                for (std::string str : _args){
                    std::cout << "Found arg: " << str << std::endl;
                }
                this->functionMappings[*(it-1)](_args);
            }
        }
    }

}
void MissMoss::Script::ScriptProcessor::ProcessLines(MissMoss::Types::tokens linesToProcess){
    for (std::string line : linesToProcess){
        this->ProcessLine(line);
    }
}
void MissMoss::Script::ScriptProcessor::setSetting(std::pair<std::string,std::string> setting){
    this->settings[setting.first] = setting.second;
}

void MissMoss::Script::ScriptProcessor::dumpSettings(std::string &string){
    string = "{";
    for (std::string key : MissMoss::Script::getMapKeys<std::string,std::string>(this->settings)){
        string += (key + ":" + this->settings[key] + ",");
    }
    string = string.substr(0,string.length()-1);
    string += "}";
}

void MissMoss::Script::ScriptProcessor::dumpSettings(std::ostream &stream, const char *end)
{
    std::string temp;
    dumpSettings(temp);
    stream << temp << end;
}

void MissMoss::Script::ScriptProcessor::registerFunction(std::string alias, MissMoss::Types::function functionRef){
    this->functionMappings[alias] = functionRef;
}

#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif