#include <iostream>
#include "Double_sentinel_list.h"

// Every C++ Project in Visual Studio and other IDEs can only have one file with a main() function.
// Thus, if you want this to compile, you must change the name to 'main()' and change the name of
// the 'main()' function in the driver to something else.
int main() {
	Double_sentinel_list<int>* list = new Double_sentinel_list<int>();
    list->push_front(5);

/*	std::cout << "The list should be empty (1): " << list.empty() << std::endl;
	std::cout << "The size should be 0: " << list.size() << std::endl;
	std::cout << "The next pointer of begin should be the null pointer: " << list.begin()->next() << std::endl;
	std::cout << "The begin should equal end: " << (list.begin() == list.end()) << std::endl;*/

//	list.push_front(1);
//    list.push_front(2);
//    list.push_front(3);
//    list.push_front(4);


/*	std::cout << "The value of the node returned by begin should be 5: " << list.begin()->value() << std::endl;
	std::cout << "The value of the front should be 5: " << list.front() << std::endl;
	std::cout << "The value of the node returned by rbegin should be 5: " << list.rbegin()->value() << std::endl;
	std::cout << "The value of the back should be 5: " << list.back() << std::endl;*/

/*    std::cout << "Found value " << list.find(7)->value() << " at address " << list.find(7) << std::endl;
    std::cout << "Found " << list.count(7) << " instance(s) of value 7" << std::endl;
    std::cout << "Erasing " << list.count(7) << " instance(s) of value 7..." << std::endl;
    list.erase(5);
    std::cout << list.count(7) << " values of 7 remaining" << std::endl << std::endl;

    std::cout << list << std::endl;
    list.pop_front();
    std::cout << list << std::endl;*/


//    list.pop_front();
//    std::cout << list << std::endl;

    Double_sentinel_list<int> copied_list(*list);
    std::cout << copied_list << std::endl;

    Double_sentinel_list<int> move_list = Double_sentinel_list<int>(std::move(*list));
    std::cout << move_list << std::endl;
    std::cout << list << std::endl;
    delete list;
//	std::cin.get();
//    delete list;
	return 0;
}
