#include <iostream>
#include <set>
#include "clothing.h"
#include "util.h"
#include <string>
#include <sstream>

using namespace std;

Clothing::Clothing(string category, string name, double price, int qty, std::string size, std::string brand):
	Product(category,name,price,qty)
{
	size_ = size;
	brand_ = brand;
}

set<string> Clothing::keywords() const{
	set<string> output = parseStringToWords(name_);
	set<string> brandname = parseStringToWords(brand_);

	for (set<string>::iterator it = brandname.begin(); it != brandname.end(); ++it){
		output.insert(*it);
	}

	return output;
}

string Clothing::displayString() const{
	stringstream ss;
	ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left." << endl;
	return ss.str();
}

void Clothing::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<"\n" << size_ << "\n" << brand_ << endl;
}