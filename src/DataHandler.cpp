#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <nlohmann/json.hpp>
#include "../include/MossLib/DataHandler.hpp"

namespace Moss {
    namespace Data {
        template <typename T1, typename T2>
        BiMap<T1,T2>::BiMap(){

        }

        template <typename T1, typename T2>
        BiMap<T1,T2>::BiMap(std::pair<T1,T2> _const){
            this->data.push_back(_const);
        }

        template <typename T1, typename T2>
        BiMap<T1,T2>::BiMap(std::vector<std::pair<T1,T2>> _const){
            this->data = _const;
        }

        template <typename T1, typename T2>
        T1 &BiMap<T1,T2>::operator[](T2 _seek){
            for (std::vector<std::pair<T1,T2>>::iterator it = this->data.begin(); it != this->data.end(); it++) {
                if ((*it).second == _seek){
                    return (*it).first;
                }
            }
        }

        template <typename T1, typename T2>
        T2 &BiMap<T1,T2>::operator[](T1 _seek){
            for (std::vector<std::pair<T1,T2>>::iterator it = this->data.begin(); it != this->data.end(); it++) {
                if ((*it).first == _seek){
                    return (*it).second;
                }
            }
        }

        template <typename T1, typename T2>
        BiMap<T1,T2> &BiMap<T1,T2>::append(std::pair<T1,T2> _app){
            this->data.push_back(_app);
        }

        template <typename T1, typename T2>
        BiMap<T1,T2> &BiMap<T1,T2>::append(std::vector<std::pair<T1,T2>> _app){
            this->data.push_back(_app);
        }
    }
}