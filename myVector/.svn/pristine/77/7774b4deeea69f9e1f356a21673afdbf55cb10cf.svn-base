#include <iostream>

std::ostream& operator<<(std::ostream& os, const Product& p) {
	os << p.name_ << " " << p.quantity_ << " " << p.price_;
	return os;
}

Product::Product(Product& p) {
	strcpy(name_, p.name_);
	quantity_ = p.quantity_;
	price_ = p.price_;
}

Product::Product(const char* name, int quantity, double price) {
	strcpy(name_, name);
	quantity_ = quantity;
	price_ = price;	
}