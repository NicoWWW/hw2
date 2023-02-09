#include <string>
#include "mydatastore.h"
#include <set>
#include <vector>
#include <map>

using namespace std;

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
	for (map<string,Product*>::iterator it=productMap.begin(); it!=productMap.end(); ++it){
		delete it->second;
	}
	for (map<string,User*>::iterator it=userMap.begin(); it!=userMap.end(); ++it){
		delete it->second;
	}
}

void MyDataStore::addProduct(Product* p){
	productMap.insert(make_pair(p->getName(),p));
	set<string> tempkeywords = p->keywords();
	set<string>::iterator i;//iterator for p's keywords set
	map<string, set<Product*>>::iterator j;//iterator for keywordsToProducts

	for (i=tempkeywords.begin(); i!=tempkeywords.end(); ++i){
		j = keywordsToProducts.find(*i);
		if (j == keywordsToProducts.end()){
			set<Product*> temp;
			temp.insert(p);
			keywordsToProducts.insert(make_pair(*i,temp));
		}
		else{
			(j->second).insert(p);
		}
	}
}

void MyDataStore::addUser(User* u){
	userMap.insert(make_pair(u->getName(),u));
	cartOfUsers.insert(make_pair(u->getName(),NULL));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	set<Product*> temp;
	vector<Product*> output;
	if (type == 0){
		temp = keywordsToProducts[terms[0]];
		for (unsigned int i=1; i<terms.size(); i++){
			temp = setIntersection(temp, keywordsToProducts[terms[i]]);
		}
		for (set<Product*>::iterator it=temp.begin(); it!=temp.end(); ++it){
			output.push_back(*it);
		}
	}
	else if(type == 1){
		temp = keywordsToProducts[terms[0]];
		for (unsigned int i=1; i<terms.size(); i++){
			temp = setUnion(temp, keywordsToProducts[terms[i]]);
		}
		for (set<Product*>::iterator it=temp.begin(); it!=temp.end(); ++it){
			output.push_back(*it);
		}
	}
	return output;
}

void MyDataStore::dump(std::ostream& ofile){
	map<string,Product*>::iterator i;
	map<string,User*>::iterator j;
	ofile << "<products>"<<endl;
	for (i=productMap.begin(); i!=productMap.end(); ++i){
		i->second->dump(ofile);
	}
	ofile<<"</products>"<<endl;
	ofile<<"<users>"<<endl;
	for (j=userMap.begin(); j!=userMap.end(); ++j){
		j->second->dump(ofile);
	}
	ofile<<"</users>"<<endl;
}

void MyDataStore::addToCart(std::string user, Product* p){
	bool found = false; 
  map<string, vector<Product*>>::iterator k = cartOfUsers.find(user); 
  for (k = cartOfUsers.begin(); k != cartOfUsers.end(); ++k)
  {
    if (k->first == user) 
    {
      (k->second).push_back(p);
      found = true; 
    }
  }
  if (!found)
  {
    cout << "Invalid request" << endl; 
  }
}

void MyDataStore::viewCart(std::string user){
	if(cartOfUsers.find(user) != cartOfUsers.end()){
		int cnt = 1;
		for (vector<Product*>::iterator it = cartOfUsers[user].begin(); it != cartOfUsers[user].end(); ++it){
			cout << "Item " << cnt << endl;
			cout << (*it)->displayString() <<endl;
			cnt++;
		}
	}
	else{
		cout << "Invalid Username" <<endl;
	}
}

void MyDataStore::buyCart(std::string user){
	map<string,vector<Product*>>::iterator ittemp = cartOfUsers.find(user);
	if (ittemp == cartOfUsers.end()){
		cout << "Invalid Username" <<endl;
		return;
	}
	else{
		for (vector<Product*>::iterator it = cartOfUsers[user].begin(); it!=cartOfUsers[user].end();){
			if ((*it)->getQty()>=1 && userMap[user]->getBalance() >= (*it)->getPrice()){
				(*it)->subtractQty(1);
				userMap[user]->deductAmount((*it)->getPrice());
				cartOfUsers[user].erase(it);
			}
			else{
				++it;
			}
		}
	}
}
