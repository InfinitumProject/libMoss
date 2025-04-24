#include "../../../include/libMoss/network.hpp"
#include "../../../include/libMoss/debug.hpp"
#include "../server.cpp"

#include <chrono>
#include <functional>

using namespace std::chrono_literals;

int main(){
    try {
        std::thread e(&server,1234);
    
        Moss::Network::TCP conn1("127.0.0.1",1234);
        Moss::Network::TCP conn2("127.0.0.1",1234);
    
        conn1 << "This is a test from C1.";
        conn1 << "EWAEWEADAS";
        conn1 << EXIT_PACKET;
        conn2 << "This is a test from C2.";
        conn2 << "Ooooh.. keysmash... ABGAJSBGJBAG!!!!";
        conn2 << EXIT_PACKET;
    
        std::this_thread::sleep_for(1s);
        Moss::Network::TCP closer("127.0.0.1",1234);
        closer << STOP_PACKET;
        e.join();
        return 0;
    } catch (...) {
        return -1;
    }
}