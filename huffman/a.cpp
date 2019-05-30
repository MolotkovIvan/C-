#include <iostream>
#include <fstream>

int main() {
    std::ofstream out("in.txt", std::ios::binary | std::ios::out);
    for (int i = 0; i < 2; i++) {
        out << (char)('a'+i);
    }    
    return 0;
}
