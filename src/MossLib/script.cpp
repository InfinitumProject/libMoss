#ifdef __linux__
#include <string>
#include <filesystem>
#include <fstream>
#include "../../include/MissMoss/script.hpp"
#include "../../include/MissMoss/types.hpp"

namespace MissMoss::Script {
    tokens tokenize(std::string input, char delim, bool append_delim){
        tokens output;
        int last = 0, current;
        for (int i = 0; i < input.length(); i++){
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

    void tokenize(std::string input, char delim, bool append_delim, tokens &output){
        int last = 0, current;
        for (int i = 0; i < input.length(); i++){
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

    tokens multiTokenize(std::string input, std::vector<char> delim){
        tokens output;
        int last = 0, current;
        for (int i = 0; i < input.length(); i++){
            for (char del : delim){
                if (input[i] == del){
                    current = i;
                    output.push_back(input.substr(last, current - last));
                    last = i;
                }
            }
        }
        return restringTokens(output);
    }

    void multiTokenize(std::string input, std::vector<char> delim, tokens &output){
        tokens outputBuffer;
        int last = 0, current;
        for (int i = 0; i < input.length(); i++){
            for (char del : delim){
                if (input[i] == del){
                    current = i;
                    outputBuffer.push_back(input.substr(last, current - last));
                    last = i;
                }
            }
        }
        restringTokens(outputBuffer, output);
    }

    tokens restringTokens(tokens &_tokens){
        tokens output;
        bool isInQuotes = false;
        std::string buffer;
        for (int i = 0; i < _tokens.size(); i++){
            if (_tokens[i][0] == '"'){
                if (isInQuotes){
                    isInQuotes = false;
                    buffer.append(_tokens[i]);
                    output.push_back(buffer);
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

    void restringTokens(tokens &_tokens, tokens &output){
        bool isInQuotes = false;
        std::string buffer;
        for (int i = 0; i < _tokens.size(); i++){
            if (_tokens[i][0] == '"'){
                if (isInQuotes){
                    isInQuotes = false;
                    buffer.append(_tokens[i]);
                    output.push_back(buffer);
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

    template <typename T1,typename T2>
    std::vector<T1> getMapKeys(std::map<T1,T2> &input){
        std::vector<T1> keys;
        for (auto it = input.begin(); it != input.end(); ++it){
            // Add the key to the vector
            keys.push_back(it->first);
        }
        return keys;
    }
}

MissMoss::Script::ScriptProcessor::ScriptProcessor(){
    this->delims = {';','(',')',',','"',' ','{','}','[',']','\''};
}
int MissMoss::Script::ScriptProcessor::ProcessLine(std::string lineToProcess){
    if (lineToProcess[0] == '#'){
        std::string *buffer = new std::string(lineToProcess.substr(1));
        std::pair<std::string,std::string> *settingData = new std::pair<std::string,std::string>({tokenize(*buffer,' ',false)[0],tokenize(*buffer,' ',false)[1]});
        this->setSetting(*settingData);
        delete settingData;
        delete buffer;
        return 1;
    } else {
        tokens tokenizedLine;
        multiTokenize(lineToProcess,this->delims,tokenizedLine);
    }

}
int MissMoss::Script::ScriptProcessor::ProcessLines(tokens linesToProcess){
    for (std::string line : linesToProcess){
        this->ProcessLine(line);
    }
    return 1;
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

void MissMoss::Script::ScriptProcessor::registerFunction(std::string alias, std::function<int(void*)> functionRef){
    this->functionMappings[alias] = functionRef;
}

#elif _WIN32
//to be completed (I use linux so I can't dev Windows side of the lib often)
#endif