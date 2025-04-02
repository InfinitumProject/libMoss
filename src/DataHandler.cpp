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
            for (int i = 0; i < this->data.size(); i++) {
                if (this->data[i].second == _seek) {
                    return this->data[i].first;
                }
            }
            throw noValue();
            return dummyT1;
        }

        template <typename T1, typename T2>
        T2 &BiMap<T1,T2>::operator[](T1 _seek){
            for (int i = 0; i < this->data.size(); i++) {
                if (this->data[i].first == _seek) {
                    return this->data[i].second;
                }
            }
            throw noValue();
            return dummyT2;
        }

        template <typename T1, typename T2>
        BiMap<T1,T2> &BiMap<T1,T2>::append(std::pair<T1,T2> _app){
            this->data.push_back(_app);
            return *this;
        }

        template <typename T1, typename T2>
        BiMap<T1,T2> &BiMap<T1,T2>::append(std::vector<std::pair<T1,T2>> _app){
            this->data.push_back(_app);
        }
        
        template <typename T1, typename T2>
        typename BiMap<T1,T2>::iterator BiMap<T1,T2>::begin(){
            return BiMap::iterator(this,0);
        }

        template <typename T1, typename T2>
        typename BiMap<T1,T2>::iterator BiMap<T1,T2>::end(){
            return BiMap::iterator(this,this->data.size()-1);
        }

        template <typename T1, typename T2>
        BiMap<T1,T2>::iterator::iterator(BiMap<T1,T2> &_source){
            this->source = _source;
            this->position = 0;
        }

        template <typename T1, typename T2>
        BiMap<T1,T2>::iterator::iterator(BiMap<T1,T2> &_source, int _pos){
            this->source = _source;
            this->position = _pos;
        }

        template <typename T1, typename T2>
        BiMap<T1,T2>::iterator::iterator(BiMap<T1,T2> *_source){
            this->source = _source;
            this->position = 0;
        }

        template <typename T1, typename T2>
        BiMap<T1,T2>::iterator::iterator(BiMap<T1,T2> *_source, int _pos){
            this->source = _source;
            this->position = _pos;
        }

        template <typename T1, typename T2>
        std::pair<T1,T2> &BiMap<T1,T2>::iterator::operator*(){
            return this->source->data[this->position];
        }

        template <typename T1, typename T2>
        typename BiMap<T1,T2>::iterator &BiMap<T1,T2>::iterator::operator++(){
            this->position++;
            return *this;
        }

        template <typename T1, typename T2>
        typename BiMap<T1,T2>::iterator &BiMap<T1,T2>::iterator::operator--(){
            this->position--;
            return *this;
        }

        template <typename T1, typename T2>
        typename BiMap<T1,T2>::iterator &BiMap<T1,T2>::iterator::operator++(int){
            return *this;
            this->position++;
        }

        template <typename T1, typename T2>
        typename BiMap<T1,T2>::iterator &BiMap<T1,T2>::iterator::operator--(int){
            return *this;
            this->position--;
        }

        template <typename T1, typename T2>
        typename BiMap<T1,T2>::iterator BiMap<T1,T2>::iterator::operator+(int _change){
            return iterator(this->source,this->position+_change);
        }

        template <typename T1, typename T2>
        typename BiMap<T1,T2>::iterator BiMap<T1,T2>::iterator::operator-(int _change){
            return iterator(this->source,this->position-_change);
        }

        template <typename T1, typename T2>
        bool BiMap<T1,T2>::iterator::operator==(BiMap<T1,T2>::iterator _other){
            return (this->position == _other.position);
        }

        template <typename T1, typename T2>
        bool BiMap<T1,T2>::iterator::operator!=(BiMap<T1,T2>::iterator _other){
            return (this->position != _other.position);
        }
    }
}