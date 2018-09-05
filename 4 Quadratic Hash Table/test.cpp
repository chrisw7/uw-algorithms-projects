#include <iostream>
#include "Quadratic_hash_table.h"

int main() {
	//Quadratic_hash_table<int>* tab = new Quadratic_hash_table<int>(-6);

	//std::cout << "Size: " << tab->size() << std::endl;
	//std::cout << "Capacity: " << tab->capacity() << std::endl;
	//std::cout << "Load: " << tab->load_factor() << std::endl;
	//std::cout << "Empty?: " << tab->empty() << std::endl;

	//tab->insert(31);
	//tab->insert(191);
	//tab->insert(159);
	//tab->insert(3);
	//tab->insert(4);
	//tab->insert(5);
	//tab->insert(6);
	//tab->insert(7);
	////tab->insert(8);

	//std::cout << *tab << std::endl;

	//std::cout << "Erase 111?: " << tab->erase(111) << std::endl;
	//std::cout << "Erase 159?: " << tab->erase(159) << std::endl;
	//std::cout << "Member 05?: " << tab->member(5) << std::endl;

	//std::cout << *tab << std::endl;

	//tab->clear();

	//std::cout << std::endl << "Clear" << std::endl << std::endl;

	//std::cout << "Size: " << tab->size() << std::endl;
	//std::cout << "Capacity: " << tab->capacity() << std::endl;
	//std::cout << "Load: " << tab->load_factor() << std::endl;
	//std::cout << "Empty?: " << tab->empty() << std::endl;

	//
	//std::cout << *tab;

	//Quadratic_hash_table<double>* tab2 = new Quadratic_hash_table<double>(2);

	//tab2->insert(0.2499242);
	//tab2->insert(-0.13228);
	//tab2->insert(-912341234);
	//tab2->insert(-292341234);
	//std::cout << "Size: " << tab2->size() << std::endl;

	//tab2->erase(0.2499242);
	//std::cout << *tab2 << std::endl;
	//std::cout << "Size: " << tab2->size() << std::endl;

	//tab2->insert(77777);
	//std::cout << *tab2 << std::endl;
	//std::cout << "Size: " << tab2->size() << std::endl;

	//tab2->erase(77777);
	//std::cout << *tab2 << std::endl;
	//std::cout << "Size: " << tab2->size() << std::endl;

	Quadratic_hash_table<double>* tab2 = new Quadratic_hash_table<double>(2);
	tab2->insert(0.2499242);
	tab2->insert(-0.13228);
	tab2->insert(-912341234);
	tab2->insert(-292341234);
	tab2->insert(-292341234);


	std::cin.get();
	return 0;
}