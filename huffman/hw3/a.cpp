#include <iostream>
#include <fstream>

int main() {
    std::ofstream out("in.txt", std::ios::binary | std::ios::out);
    for (int i = 0; i < 5; i++) {
        out << 'a';
    }    
    return 0;
}
