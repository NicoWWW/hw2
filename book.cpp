#include <iostream>
#include <set>
#include "book.h"
#include "util.h"
#include <string>
#include <sstream>

using namespace std;

Book::Book(string category, string name, double price, int qty, std::string isbn, std::string author):
	Product(category,name,price,qty)
{
	isbn_ = isbn;
	author_ = author;
}

set<string> Book::keywords() const{
	set<string> output = parseStringToWords(name_);
	set<string> authorname = parseStringToWords(author_);

	for (set<string>::iterator it = authorname.begin(); it != authorname.end(); ++it){
		output.insert(*it);
	}

	output.insert(isbn_);
	return output;
}

string Book::displayString() const{
	stringstream ss;
	ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left." << endl;
	return ss.str();
}

void Book::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<"\n" << isbn_ << "\n" << author_ << endl;
}