#include <iostream>
#include "Search_tree.h"

int main() {
	Search_tree<int> tree;

    std::cout << tree.insert( 7 );
    std::cout << tree.insert( 9 );
    std::cout << tree.insert( 17 );

    std::cout << std::endl;

	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    tree.clear();
    std::cout << tree.insert( 7 );
    std::cout << tree.insert( 15 );
    std::cout << tree.insert( 6 );
    std::cout << tree.insert( 26 );
    std::cout << tree.insert( 9 );
    std::cout << tree.insert( 17 );

    std::cout << std::endl;

    std::cout << "Front:   " << tree.front()   << std::endl;
    std::cout << "Back:    " << tree.back()    << std::endl;
    std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    /*tree.clear();
    std::cout << tree.insert( 17 );
    std::cout << tree.insert( 9 );
    std::cout << tree.insert( 26 );
    std::cout << tree.insert( 6 );
    std::cout << tree.insert( 15 );
    std::cout << tree.insert( 21 );
    std::cout << tree.insert( 29 );
    std::cout << tree.insert( 5 );
    std::cout << tree.insert( 8 );
    std::cout << tree.insert( 12 );
    std::cout << tree.insert( 16 );

    std::cout << tree.insert( 7 );

    std::cout << std::endl;

    std::cout << "Front:   " << tree.front()   << std::endl;
    std::cout << "Back:    " << tree.back()    << std::endl;
    std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;*/


    /*tree.insert(21);
    tree.insert(8);
    tree.insert(34);
    tree.insert(3);
    tree.insert(16);
    tree.insert(26);
    tree.insert(42);
    tree.insert(2);
    tree.insert(5);
    tree.insert(11);
    tree.insert(18);
    tree.insert(23);
    tree.insert(31);
    tree.insert(37);
    tree.insert(47);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);
    tree.insert(13);
    tree.insert(17);
    tree.insert(19);
    tree.insert(22);
    tree.insert(24);
    tree.insert(28);
    tree.insert(33);
    tree.insert(35);
    tree.insert(40);
    tree.insert(45);
    tree.insert(52);
    tree.insert(7);
    tree.insert(10);
    tree.insert(12);
    tree.insert(14);
    tree.insert(20);
    tree.insert(25);
    tree.insert(27);
    tree.insert(30);
    tree.insert(32);
    tree.insert(36);
    tree.insert(38);
    tree.insert(41);
    tree.insert(43);
    tree.insert(46);
    tree.insert(49);
    tree.insert(53);
    tree.insert(15);
    tree.insert(29);
    tree.insert(39);
    tree.insert(44);
    tree.insert(48);
    tree.insert(51);
    tree.insert(54);
    tree.insert(50);

    tree.erase(1);*/

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	tree.clear();

	std::cout << "--> ";
	

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cin.get();
	return 0;
}
