#include "employees.h"
#include <iostream>
#include <fstream>
#include <string>

int main(){
	std::string command;
	EmployeesArray array;
	while (command.compare("exit") != 0) {
		std::cin >> command;
		if (command.compare("load") == 0) {
			std::string filename;
			std::cin >> filename;
			std::ifstream in(filename.c_str(), std::ios::binary | std::ios::in);
			in >> array;
			in.close();
		} else if (command.compare("list") == 0) {
			std::cout << array << std::endl;
		} else if (command.compare("add") == 0) {
			int type;
			std::cin >> type;
			if (type == 1) {
				Developer* e = new Developer;
				std::cin >> *e;
				array.add(e);
			} else if (type == 2) {
				SalesManager* e = new SalesManager;
				std::cin >> *e;
				array.add(e);
			}
		} else if (command.compare("save") == 0) {
			std::string filename;
			std::cin >> filename;
			std::ofstream out(filename.c_str(), std::ios::binary | std::ios::out);
			out << array;
			out.close();
		} 
	}
	return 0;
}