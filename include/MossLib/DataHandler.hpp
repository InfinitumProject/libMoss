#include <nlohmann/json.hpp>

namespace Moss {
    namespace Data {
        template <typename T1, typename T2>
        class BiMap {
            std::vector<std::pair<T1,T2>> data;
            public:
            BiMap();
            BiMap(std::pair<T1,T2>);
            BiMap(std::vector<std::pair<T1,T2>>);
            T1 &operator[](T2);
            T2 &operator[](T1);
            BiMap &append(std::pair<T1,T2>);
            BiMap &append(std::vector<std::pair<T1,T2>>);

            class iterator {
                BiMap *source;
                int position;
                public:
                iterator(BiMap&, int);
                iterator(BiMap*, int);
                iterator(BiMap&);
                iterator(BiMap*);

                std::pair<T1,T2> &operator*();
                iterator &operator++();
                iterator &operator--(int);
                iterator &operator++();
                iterator &operator--(int);
                iterator operator+(int);
                iterator operator-(int);
            };

            iterator begin();
            iterator end();
        };

        class DataManager {
            private:
            nlohmann::json data;
            std::map<std::string,char> dataMappings;
            public:
            DataManager(){};
            std::string encode(std::string);
            void load(std::string);
            void save(std::string);
        };
    }
}
