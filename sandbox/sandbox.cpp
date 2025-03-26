#include "../include/MissMoss/types.hpp"
#include <iostream>

using namespace MissMoss::Types;

template <typename T1, typename... T2>
class test {
    public:
    test(std::function<void*(void*...)> Func) : intFunc(Func) {}
    int argLength = sizeof(T2);
    private:
    std::function<void*(void*[])> intFunc;
    T1 operator()(T2... args){
        return (T1)intFunc((T2...)args...);
    }
    
};

int main(){

    


    return 0;
}