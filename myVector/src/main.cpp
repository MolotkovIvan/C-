#include <iostream>
#include <cstring>
#include "my_vector.h"

class Product {
public:
    Product(const char* name, int quantity, double price);
    Product(Product&);
    Product() {}
    friend std::ostream& operator<<(std::ostream&, const Product&);
private:
    char *name_;
    int quantity_;
    double price_;
};

std::ostream& operator<<(std::ostream& os, const Product& p) {
	os << p.name_ << " " << p.quantity_ << " " << p.price_;
	return os;
}

Product::Product(Product& p) {
	name_ = new char[strlen(p.name_)+1];
	strcpy(name_, p.name_);
	quantity_ = p.quantity_;
	price_ = p.price_;
}

Product::Product(const char* name, int quantity, double price) {
	name_ = new char[strlen(name)+1];
	strcpy(name_, name);
	quantity_ = quantity;
	price_ = price;	
}

void test_my_vector() {
	Product a("asd", 4, 11.0);
	Product b = a;
	Product c("efc", 1, 12.0);
	my_vector<Product> v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	std::cout << v << "\n";	
	v.erase(1);
	std::cout << v << "\n";	
	v.pop_back();
	if (v.empty()) {
		std::cout << "empty\n"; 
	} else {
		std::cout << v << "\n";
	}
	v.pop_back();
	if (v.empty()) {
		std::cout << "empty\n"; 
	} else {
		std::cout << v << "\n";
	}

	int a2 = 5;
	int b2 = a2;
	my_vector<int> v2;
	v2.push_back(a2);
	v2.push_back(b2);
	v2.push_back(14);
	std::cout << v2 << "\n";
	v2.pop_back();
	std::cout << v2.empty() << "\n";
}

int main() {
	test_my_vector();
    return 0;
}