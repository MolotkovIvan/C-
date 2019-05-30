#include "matrix.h"
#include <iostream>
#include <string>
#include <fstream>

int main() {
	Matrix* m = new Matrix[10];
	std::string cmd;
	while (cmd.compare("exit") != 0) {
		std::cin >> cmd;
		if (cmd.compare("load") == 0) {
			std::string reg, filename;
			std::cin >> reg >> filename;
			int n = reg[1] - '0';
			std::ifstream in(filename.c_str());
			in >> m[n];
			in.close();
		} else if (cmd.compare("print") == 0) {
			std::string reg;
			std::cin >> reg;
			int n = reg[1] - '0';
			std::cout << m[n];
		} else if (cmd.compare("add") == 0) {
			std::string reg1, reg2;
			std::cin >> reg1 >> reg2;
			int n1 = reg1[1] - '0', n2 = reg2[1] - '0';			
			try {
				m[n1] += m[n2];
			}
			catch (MatrixException& e){
				std::cout << e.get() << "\n";
			}
		} else if (cmd.compare("mul") == 0) {
			std::string reg1, reg2;
			std::cin >> reg1 >> reg2;
			int n1 = reg1[1] - '0', n2 = reg2[1] - '0';			
			try {
				m[n1] *= m[n2];
			}
			catch (MatrixException& e){
				std::cout << e.get() << "\n";
			}
			
		} else if (cmd.compare("elem") == 0) {
			std::string reg;
			int x, y;
			std::cin >> reg >> x >> y;
			int n = reg[1] - '0';			
			try {
				std::cout << m[n].get(x,y) << "\n";
			}
			catch (MatrixException& e){
				std::cout << e.get() << "\n";
			}			
		}
	}
	delete [] m;
	return 0;
}