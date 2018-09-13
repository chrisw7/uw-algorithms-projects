## Project 4: [Quadratic Hash Table](<4 Quadratic Hash Table/>)

> | Complete?			| Description 	| Grade |
> | :---: 				| :--- 			| --- 	|
> | :heavy_check_mark:	| \<Type\> templated hash table with open addressing (quadratic probing) and Ө(1) operations for load factors < ~0.666  | **8/8** (100%) |

The hash function (that determining the initial bin) is the object statically cast as an int (see static_cast<int>), taking this integer module M (i % M), and adding M if the value is negative.

**Full Description:** https://ece.uwaterloo.ca/~dwharder/aads/Projects/4/Quadratic_hash_table/
   
##### Member Variables
- An array of objects Type *array,
- An array size int array_size, and
- A count int count.

##### Accessors
This class has seven accessors:

- `int size() const`
	- Returns the number of elements currently stored in the hash table. (Θ(1))
- `int capacity() const
	- Returns the number of bins in the hash table. (Θ(1))
double load_factor() const`
Returns the load factor of hash table (see static_cast<double>(...)). This should be the ratio of occupied and erased bins over the total number of bins. (Θ(1))
- `bool empty() const`
	- Returns true if the hash table is empty, false otherwise. (Θ(1))
`bool member( Type const & ) const
	- Returns true if object obj is in the hash table and false otherwise. (Θ(1) under our assumptions)
- `Type bin( int n ) const`
	- Return the entry in bin n. The behaviour of this function is undefined if the bin is not filled. It will only be used to test locations that are expected to be filled by specific values. (Θ(1))
- `void print() const`
	- A function which you can use to print the class in the testing environment. This function will not be tested.
##### Mutators

- `void insert( Type const & )`
	- Insert the argument into the hash table in the appropriate bin as determined by the aforementioned hash function and the rules of quadratic hashing. If the table is full, thrown an overflow exception. If the hash table is not full and the argument is already in the hash table, do nothing. An object can be placed either into an empty or deleted bin. Do not rehash the entries even if there are many erased bins. (Θ(1) under our assumption of a small load factor)
- `bool erase( Type const & )`
	- Remove the argument from the hash table if it is in the hash table (returning false if it is not) by setting the corresponding flag of the bin to deleted. (Θ(1) under our assumption of a small load factor)
- `void clear()`
	- Removes all the elements in the hash table by setting all entries to unoccupied. (Θ(M))