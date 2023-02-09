#include <iostream>
#include <set>
#include "movie.h"
#include "util.h"
#include <string>
#include <sstream>

using namespace std;

Movie::Movie(string category, string name, double price, int qty, std::string genre, std::string rating):
	Product(category,name,price,qty)
{
	genre_ = genre;
	rating_ = rating;
}

set<string> Movie::keywords() const{
	set<string> output = parseStringToWords(name_);
	set<string> genrename = parseStringToWords(genre_);

	for (set<string>::iterator it = genrename.begin(); it != genrename.end(); ++it){
		output.insert(*it);
	}

	return output;
}

string Movie::displayString() const{
	stringstream ss;
	ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left." << endl;
	return ss.str();
}

void Movie::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<"\n" << genre_ << "\n" << rating_ << endl;
}