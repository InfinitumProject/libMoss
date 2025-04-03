#pragma once
#include <nlohmann/json.hpp>

namespace Moss {
    namespace Data {
        /**
         * @tparam T1 The first type in the bimap.
         * @tparam T2 The second type in the bimap.
         */
        template <typename T1, typename T2>
        /*using val_type = typename std::enable_if<
                    !std::is_same<T1,T2>::value,
                    T2
                >::type;*/
        class bimap {
            static_assert(!std::is_same<T1,T2>::value,"Error: The provided typenames for a bimap cannot be the same at this moment.");
            /**
             * @brief An uninitialized dummy value to return when the operator[] method throws an
             * exception to silence compiler errors regarding return statements in all execution paths.
             */
            T1 dummyT1;
            /**
             * @brief An uninitialized dummy value to return when the operator[] method throws an
             * exception to silence compiler errors regarding return statements in all execution paths.
             */
            T2 dummyT2;
            /**
             * @brief The data held in the bimap, that should be pretty self explanatory honestly.
             */
            std::vector<std::pair<T1,T2>> data;
            public:
            /**
             * @brief A constructor that takes no arguments.
             */
            bimap();
            /**
             * @brief A constructor that takes a singular pair.
             * @param _const The pair to initialize the data with.
             */
            bimap(std::pair<T1,T2>);
            /**
             * @brief A constructor that takes a vector of pairs.
             * @param _const The vector to initialize the data with.
             */
            bimap(std::vector<std::pair<T1,T2>>);
            /**
             * @brief A lookup operator.
             * @param _seek The thing to look for.
             * @returns The value that is associated with the input value.
             */
            T1 &operator[](T2);
            /**
             * @brief A lookup operator.
             * @param _seek The thing to look for.
             * @returns The value that is associated with the input value.
             */
            T2 &operator[](T1);
            /**
             * @brief Appends a pair to the bimap.
             * @param _data The pair to append.
             */
            bimap &append(std::pair<T1,T2>);
            /**
             * @brief Appends a vector of pairs to the bimap.
             * @param _data The vector to append.
             */
            bimap &append(std::vector<std::pair<T1,T2>>);

            /**
             * @brief A custom made iterator for moving through data in the bimap.
             */
            class iterator {
                /**
                 * @brief The source bimap for the iterator.
                 */
                bimap *source;
                /**
                 * @brief The index/position of the iterator in the bimap.
                 */
                int position;
                public:
                /**
                 * @brief A constructor for a bimap iterator.
                 * @param _source The source bimap to access data from.
                 * @param _pos The position of the iterator at construction.
                 */
                iterator(bimap&, int);
                /**
                 * @brief A constructor for a bimap iterator.
                 * @param _source A pointer to the source bimap to access data from.
                 * @param _pos The position of the iterator at construction.
                 */
                iterator(bimap*, int);
                /**
                 * @brief A constructor for a bimap iterator.
                 * @param _source The source bimap to access data from.
                 */
                iterator(bimap&);
                /**
                 * @brief A constructor for a bimap iterator.
                 * @param _source A pointer to the source bimap to access data from.
                 */
                iterator(bimap*);

                /**
                 * @brief The dereference operator used to access the data at a pointer.
                 * @returns A read/write reference to the pair of data. 
                 */
                std::pair<T1,T2> &operator*();
                /**
                 * @brief A postfix increment operator. 
                 * @returns A copy of itself before incrementation.
                 */
                iterator operator++(int);
                /**
                 * @brief A postfix decrement operator. 
                 * @returns A copy of itself before decrementation.
                 */
                iterator operator--(int);
                /**
                 * @brief A prefix increment operator. 
                 * @returns A reference to itself after incrementation.
                 */
                iterator &operator++();
                /**
                 * @brief A prefix decrement operator. 
                 * @returns A reference to itself after decrementation.
                 */
                iterator &operator--();
                /**
                 * @brief References a value that is offset from the current position.
                 * @param _val How much later in sequence the referenced value is.
                 * @returns A new iterator that is at that location.
                 */
                iterator operator+(int);
                /**
                 * @brief References a value that is offset from the current position.
                 * @param _val How much earlier in sequence the referenced value is.
                 * @returns A new iterator that is at that location.
                 */
                iterator operator-(int);

                /**
                 * @brief Checks whether the iterators point to the same data from the same source.
                 * @param _other The other iterator to check.
                 * @returns A boolean value.
                 */
                bool operator==(iterator);
                /**
                 * @brief Checks whether the iterators do not point to the same data from the same source.
                 * @param _other The other iterator to check.
                 * @returns A boolean value.
                 */
                bool operator!=(iterator);
            };

            /**
             * @brief Gets an iterator pointing to the first piece of data in a bimap.
             */
            iterator begin();
            /**
             * @brief Gets an iterator pointing to the last piece of data in a bimap.
             */
            iterator end();

            /**
             * @brief An exception that is thrown when there is no value associated with the given value in an operator[] call.
             */
            class noValue : public std::exception {
                public:
                const char *what() const noexcept override {
                    return "No associated value!!!";
                }
            };
        };

        /*class DataManager {
            private:
            nlohmann::json data;
            std::map<std::string,char> dataMappings;
            public:
            DataManager(){};
            std::string encode(std::string);
            void load(std::string);
            void save(std::string);
        };*/
    }
}
