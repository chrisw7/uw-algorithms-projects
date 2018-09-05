/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  cm3willi@edu.uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Spring 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -sbregu
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -sbregu
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"		//todo ! uncomment

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
	private:
		int count;
		int erased;
		int power;
		int array_size;
		int mask;
		Type *array;
		bin_state_t *occupied;			//Array of ternary bin states

		int hash( Type const & ) const;
		int map( int ) const;	//map integer hash to integer in range 0 - array_size
		int bitmod( int ) const;

	public:
		Quadratic_hash_table( int = 5 );
		~Quadratic_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadratic_hash_table<T> const & );
};

//Constructor
template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table( int m ):
count( 0 ), power( (m >= 0) ? m : 5 ),
array_size( 1 << power ), //raise 2 to the exponent (power) using left bitwise shift
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new bin_state_t[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
}

//Destructor
template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table() {
	delete[] array;
	delete[] occupied;
}

//Private: return unique integer hash
template<typename Type>
int Quadratic_hash_table<Type>::hash(Type const &obj) const
{
	return static_cast<int>(obj);		//Return a signed int unique to this object
}

template<typename Type>
int Quadratic_hash_table<Type>::map(int hashed_value) const
{
	int mapped_value = bitmod(hashed_value);
	//If n % M is negative add M to make the result strictly positive
	return (mapped_value >= 0) ? mapped_value : mapped_value + capacity();
}

template<typename Type>
int Quadratic_hash_table<Type>::bitmod(int n) const
{
	return n & mask;					//return modulus of 2^power (replaces n % capacity())
}



//---------------------------------------------ACCESSORS

//Returns number of objects stored
template<typename Type>
int Quadratic_hash_table<Type>::size() const
{
	return count;
}

//Returns total table capacity
template<typename Type>
int Quadratic_hash_table<Type>::capacity() const
{
	return array_size;
}

//Returns fraction of filled bins
template<typename Type>
double Quadratic_hash_table<Type>::load_factor() const
{
	return (double)(count+erased)/(double)array_size;	//cast ints as double to avoid integer division
}

//Returns true for table with no stored objects
template<typename Type>
bool Quadratic_hash_table<Type>::empty() const
{
	return size() == 0;
}

//Returns true if obj is found in table
template<typename Type>
bool Quadratic_hash_table<Type>::member(Type const &obj) const
{
	int index = map(hash(obj));							//Determine index we'd expect 

	for (int k = 0; k < capacity(); k++) {
		index = bitmod(index + k);		//Quadratic probe
		if (occupied[index] == OCCUPIED && array[index] == obj) {
			return true;
		}
	}
	return false;
}

//Returns value at table index
template <typename Type>
Type Quadratic_hash_table<Type>::bin(int n) const {
	return array[n];	//return object at index n in private array
}

//Print contents of table in order
template<typename Type>
void Quadratic_hash_table<Type>::print() const
{
}

//---------------------------------------------MUTATORS

//Add an object to the table using quadratic probing; handle collisions
template<typename Type>
void Quadratic_hash_table<Type>::insert(Type const &obj)
{
	if ( size() == capacity() ) {						//Don't bother if full
		throw overflow();
	}else {												//Throw overflow for insertion to full table
		int index = map(hash(obj));						//Map the object ID to an integer < array_size
		bin_state_t occupancy;
		if (!member(obj)) {							//Only insert if member
			for (int k = 0; k < capacity(); k++) {
				index = bitmod(index + k);				//Quadratic probe
				occupancy = occupied[index];
				if (occupancy != OCCUPIED) {
					count++;
					if (occupancy == ERASED) erased--;
					array[index] = obj;
					occupied[index] = OCCUPIED;
					break;
				}
			}
		}
	}
}

//Remove an object from the table and update addresses
template <typename Type>
bool Quadratic_hash_table<Type>::erase(Type const &obj)
{
	if ( member(obj) ){
		int index = map(hash(obj));							//Identify first guess at index of bin containing obj
		for (int k = 0; k < capacity(); k++) {
			index = bitmod(index + k);		//Quadratic probe
			if (occupied[index] == OCCUPIED && array[index] == obj) {
				occupied[index] = ERASED;
				count--;
				erased++;
				return true;
			}
		}
	}
	return false;
}


//Manually empty table
template<typename Type>
void Quadratic_hash_table<Type>::clear()
{
	for (int k = 0; k < capacity(); k++) {
		occupied[k] = UNOCCUPIED;	//Mark each bin as emptied
	}
	erased = 0;
	count = 0;
}

//Override << operator for std::cout
template <typename T>
std::ostream &operator<<( std::ostream &out, Quadratic_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == UNOCCUPIED ) {
			out << "- ";
		} else if ( hash.occupied[i] == ERASED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif
