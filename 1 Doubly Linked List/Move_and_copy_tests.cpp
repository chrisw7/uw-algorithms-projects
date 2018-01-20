#include <iostream>
#include "Double_sentinel_list.h"

// Every C++ Project in Visual Studio and other IDEs can only have one file with a main() function.
// Thus, if you want this to compile, you must change the name to 'main()' and change the name of
// the 'main()' function in the driver to something else.
int main() {
	//-------------Note---------------------------------------------------------------------
	//This file contains some short examples showing how you can write code to test the
	//Double_sentinel_list's move and copy. Please read the project guide for a detailed explanation
	//of moving and copying! A quick review:

	//Assuming 2 Double_sentinal_lists, A and B:
	//Copying B into A 	-- results in A and B being two equivalent but distinct copies of B
	//									-- both A and B are usable Double_sentinal_lists after
	//Moving B into A		-- results in A "stealing" or "cannibalizing" the contents of B
	//									-- B does not have to be a valid Double_sentinal_list after, but it must still
	//										 be able to run its destructor successfully.

	//---------A brief first example----------------------------------------------------------
	//This is how to call the move and copy constructors and the copy assignment operator.
	std::cout << "Running first example\n";

	//Make two lists...
	Double_sentinel_list<int> m;
	m.push_front( 3 );
	m.push_front( 7 );
	Double_sentinel_list<int> n;
	n.push_front( 4 );
	n.push_front( 8 );

	//Copy constructor, o is a copy of m
	//Equivalently: 	Double_sentinel_list<int> o = m;
	Double_sentinel_list<int> o (m);

	//Copy assignment operator, o is a copy of n
	o = n;

	//Move constructor, p has the former contents of m
	//Equivalently: 	Double_sentinel_list<int> p = std::move(m);
	Double_sentinel_list<int> p (std::move(m));

	//Now n, o and p are usable lists, but m is not
	n.push_front( 7 );
	o.push_front( 5 );
	p.push_front( 9 );

	std::cout << "Done first example\n\n";

	//----------More detailed testing examples------------------------------------------------
	//These next examples show how to test that these functions work properly.

	//--------------Copy constructor test----------------------------------------------------
	std::cout << "Starting longer examples... \n\n";

	//Set up a small first list:
	Double_sentinel_list<int> list;
	list.push_front( 5 );
	list.push_front( 7 );

	//We can tell this calls the copy *constructor* because we are setting the non-initialized
	//list2 to be a copy of list. A constructor has not previously been called for list2.
	std::cout << "Running the copy constructor... ";
	Double_sentinel_list<int> list2 = list;
	std::cout << "finished.\n";

	//Now, list and list2 should be equivalent but separate lists:
	std::cout << "These two lists should have the same contents:\n";
	std::cout << list << "\n" << list2 << '\n';

	//And if we change one of them, the other should not be affected:
	list2.push_front( 1 );
	std::cout << "Now, list should stay the same, but list2 has an extra node:\n";
	std::cout << list << "\n" << list2 << '\n';
	list.push_front( 3 );
	std::cout << "Now, an extra 3 has been added to list but should not appear on list2:\n";
	std::cout << list << "\n" << list2 << '\n';

	//-------------Copy assignment operator test----------------------------------------------

	//Note that because list is being passed into list2 *by value* in the copy assignment operator,
	//the copy constructor is actually called first, and then the copy assignment operator function
	//is run, which is why the implementation provided in Double_sentinal_list.h swaps the two
	//lists (swapping the newly created copy from the copy constructor with the list's old contents).
	//Therefore, the copy assignent operator will not work unless your copy constructor works first!

	std::cout << "\nRunning the copy assignment operator to make list2 a copy of list ... ";
	//This is a copy assignment operator, because list2 has previously been instantiated using a constructor.
	list2 = list;
	std::cout << "finished." << "\n";

	std::cout << "Now, both list and list2 should have contents equal to what list had previously:\n";
	std::cout << list << "\n" << list2 << '\n';

	//And if we change one of them, the other should not be affected:
	list.push_front( 1 );
	list2.push_front( 3 );
	std::cout << "Now, list should have 1 in front, and list2 should have a 3 in front:\n";
	std::cout << list << "\n" << list2 << '\n';

	// -------------Move constructor tests----------------------------------------------

	//First part:-----------------------------------------------------------------------
	std::cout << "\nRunning the move constructor to give list3 the contents of list ... ";
	//This is a move constructor, because list3 has not previously been instantiated using a constructor.
	Double_sentinel_list<int> list3 = std::move(list);
	std::cout << "finished.\n";

	std::cout << "Now, list3 should have contents equal to what list had previously:\n";
	std::cout << list3 << "\n";
	//list is no longer usable and cannot be printed

	//And list3 should work properly:
	list3.push_front( 6 );
	std::cout << "Now, list3 should have 6 in front.\n";
	std::cout << list3 << "\n";

	//Second part:---------------------------------------------------------------------
	//Important note: usually it doesn't make sense to use a move with pointers. This is
	//because you could simply update	where the pointers point to instead!
	std::cout << "\nRunning example to check deletion after move\n";

	//Make a pointer to a new list, push a couple things:
	Double_sentinel_list<int> * a = new Double_sentinel_list<int>();
	a->push_front( 5 );
	a->push_front( 7 );

	//Move constructor, cannibalizing the list a points to to make the list b points to
	Double_sentinel_list<int> * b = new Double_sentinel_list<int>(std::move(*a));

	//Having done this, a can no longer be considered a usable list, and the only
	//operation guaranteed to still be valid is deleting it:
	delete a;

	//We can do more things to b if we like (unless a has incorrectly deallocated the
	//list that should now belong to b!), then finally delete it:
	b->push_front( 4 );
	b->push_front( 2 );
	delete b;

	std::cout << "Done example to check deletion after move\n";
	return 0;
}
