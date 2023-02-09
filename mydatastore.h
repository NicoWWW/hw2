#include <string>
#include "util.h"
#include "datastore.h"
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include <map>

class MyDataStore : public DataStore{
public:
	MyDataStore();
	~MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	void addToCart(std::string user, Product* p);
	void viewCart(std::string user);
	void buyCart(std::string user);

private:
	std::map<std::string, std::set<Product*>> keywordsToProducts;
	std::map<std::string, std::vector<Product*>> cartOfUsers;
	std::map<std::string, User*> userMap;
	std::map<std::string, Product*> productMap;
};