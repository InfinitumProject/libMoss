#include "../../include/MissMoss/MossLib/files.hpp"
#include <fstream>

int main(int argc,char* argv[]) {
    
    std::fstream stream;
    stream.open(argv[1],std::fstream::openmode(std::fstream::in||std::fstream::out||std::fstream::binary));
    stream << 'e';
    stream.close();

    return 0;
}