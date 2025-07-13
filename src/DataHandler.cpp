#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <nlohmann/json.hpp>
#include "../include/libMoss/DataHandler.hpp"

namespace MissMoss {
    namespace Data {
        template <typename T1, typename T2>
        bimap<T1,T2>::bimap(){

        }

        template <typename T1, typename T2>
        bimap<T1,T2>::bimap(std::pair<T1,T2> _const){
            this->data.push_back(_const);
        }

        template <typename T1, typename T2>
        bimap<T1,T2>::bimap(std::vector<std::pair<T1,T2>> _const){
            this->data = _const;
        }

        template <typename T1, typename T2>
        T1 &bimap<T1,T2>::operator[](T2 _seek){
            for (int i = 0; i < this->data.size(); i++) {
                if (this->data[i].second == _seek) {
                    return this->data[i].first;
                }
            }
            throw noValue();
            return dummyT1;
        }

        template <typename T1, typename T2>
        T2 &bimap<T1,T2>::operator[](T1 _seek){
            for (int i = 0; i < this->data.size(); i++) {
                if (this->data[i].first == _seek) {
                    return this->data[i].second;
                }
            }
            throw noValue();
            return dummyT2;
        }

        template <typename T1, typename T2>
        bimap<T1,T2> &bimap<T1,T2>::append(std::pair<T1,T2> _app){
            this->data.push_back(_app);
            return *this;
        }

        template <typename T1, typename T2>
        bimap<T1,T2> &bimap<T1,T2>::append(std::vector<std::pair<T1,T2>> _app){
            for (std::pair<T1,T2> pair : _app) {
                this->data.push_back(pair);
            }
            return *this;
        }
        
        template <typename T1, typename T2>
        typename bimap<T1,T2>::iterator bimap<T1,T2>::begin(){
            return bimap::iterator(this,0);
        }

        template <typename T1, typename T2>
        typename bimap<T1,T2>::iterator bimap<T1,T2>::end(){
            return bimap::iterator(this,this->data.size());
        }

        template <typename T1, typename T2>
        bimap<T1,T2>::iterator::iterator(bimap<T1,T2> &_source){
            this->source = _source;
            this->position = 0;
        }

        template <typename T1, typename T2>
        bimap<T1,T2>::iterator::iterator(bimap<T1,T2> &_source, int _pos){
            this->source = _source;
            this->position = _pos;
        }

        template <typename T1, typename T2>
        bimap<T1,T2>::iterator::iterator(bimap<T1,T2> *_source){
            this->source = _source;
            this->position = 0;
        }

        template <typename T1, typename T2>
        bimap<T1,T2>::iterator::iterator(bimap<T1,T2> *_source, int _pos){
            this->source = _source;
            this->position = _pos;
        }

        template <typename T1, typename T2>
        std::pair<T1,T2> &bimap<T1,T2>::iterator::operator*(){
            return this->source->data[this->position];
        }

        template <typename T1, typename T2>
        typename bimap<T1,T2>::iterator &bimap<T1,T2>::iterator::operator++(){
            this->position++;
            return *this;
        }

        template <typename T1, typename T2>
        typename bimap<T1,T2>::iterator &bimap<T1,T2>::iterator::operator--(){
            this->position--;
            return *this;
        }

        template <typename T1, typename T2>
        typename bimap<T1,T2>::iterator bimap<T1,T2>::iterator::operator++(int){
            iterator temp = *this;
            this->position++;
            return *this;
        }

        template <typename T1, typename T2>
        typename bimap<T1,T2>::iterator bimap<T1,T2>::iterator::operator--(int){
            iterator temp = *this;
            this->position--;
            return *this;
        }

        template <typename T1, typename T2>
        typename bimap<T1,T2>::iterator bimap<T1,T2>::iterator::operator+(int _change){
            return iterator(this->source,this->position+_change);
        }

        template <typename T1, typename T2>
        typename bimap<T1,T2>::iterator bimap<T1,T2>::iterator::operator-(int _change){
            return iterator(this->source,this->position-_change);
        }

        template <typename T1, typename T2>
        bool bimap<T1,T2>::iterator::operator==(bimap<T1,T2>::iterator _other){
            return (this->position == _other.position);
        }

        template <typename T1, typename T2>
        bool bimap<T1,T2>::iterator::operator!=(bimap<T1,T2>::iterator _other){
            return (this->position != _other.position);
        }
    }
}