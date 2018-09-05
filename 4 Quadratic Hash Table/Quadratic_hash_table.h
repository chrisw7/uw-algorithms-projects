/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  sbregu @edu.uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
	private:
		int count;
		int power;
		int array_size;
		int mask;
        int erasedcount;//need this since load vlaue
		Type *array;
		bin_state_t *occupied;

		int hash( Type const & ) const;

	public:
		Quadratic_hash_table( int = 5 );
		~Quadratic_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

        int hashmap( Type const &) const;//returns the mapping hash
		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadratic_hash_table<T> const & );
};

//constructor
template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table( int m ):
count( 0 ), power( ( m > 0 ) ? m : 5 ),// checking if user
array_size( 1 << power ),
mask( array_size - 1 ),
erasedcount(0),
array( new Type[array_size] ),
occupied( new bin_state_t[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
}
//destructor
template<typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table() {
    delete [] array; //deleting both arrays
    delete [] occupied;

}

template<typename Type>
int Quadratic_hash_table<Type>::hash(const Type &n) const {
	return static_cast< int>( n );
}

//accessor
template <typename Type>
int Quadratic_hash_table<Type>::size() const{
	return count;

}
template<typename Type>
int Quadratic_hash_table<Type>::capacity() const {
	return array_size;
}

template<typename Type>
double Quadratic_hash_table<Type>::load_factor() const {
	return (double) (erasedcount+size())/capacity(); //return a type double of things stored in table divided by total capacity of table
}

template<typename Type>
bool Quadratic_hash_table<Type>::empty() const {
	return size()==0;
}

template<typename Type>
bool Quadratic_hash_table<Type>::member(const Type &n) const {
    int hash_value=hashmap(n);
    for (int i=0; i<capacity(); ++i){
        if (occupied[hash_value] == OCCUPIED || occupied[hash_value]== ERASED ) {
            if (array[hash_value]==n &&  occupied[hash_value]==OCCUPIED){//if the member exists
                return true;
            }else{
                hash_value=(hash_value+i)% capacity(); //check next quadratic bin
            }
        }else{//is not a member
            return false;
        }
    }
}

template<typename Type>
Type Quadratic_hash_table<Type>::bin(int n) const {
	return array[n];
}

//mutators

template<typename Type>
void Quadratic_hash_table<Type>::insert(const Type &n) {

    int hash_value=hashmap(n);// get the mapping of the object n into its new hashed value to know which bin to store in

	if (size()==capacity()){
		throw overflow();
	} else if(member(n)){
		//do nothing
	}else{
		for (int i=0; i<capacity(); ++i){
			if (occupied[hash_value] == OCCUPIED) {
                hash_value=(hash_value+i)& mask;
			}else{
                if (occupied[hash_value]==ERASED){
                    erasedcount--;
                }
				occupied[hash_value]=OCCUPIED;//change state to occupied
				count++;
				array[hash_value]=n;
				break;
			}
		}
	}

}

template<typename Type>
bool Quadratic_hash_table<Type>::erase(const Type &obj) {

    int hash_index=hashmap(obj);

    if (member(obj)) {
        for (int i = 0; i < capacity(); ++i) {

            if (array[hash_index] == obj && occupied[hash_index]==OCCUPIED) {
                occupied[hash_index] = ERASED; // change index to erased, this allows member to keep searching even if
                count--;
                erasedcount++;
                return true;

            } else {

                hash_index = (hash_index + i) & mask;//go to next quadratic step
            }

        }
    }else{
        return false;
    }


}

template<typename Type>
void Quadratic_hash_table<Type>::clear() {
    for (int i = 0; i < capacity(); ++i) {

            occupied[i] = UNOCCUPIED;// change all states to unoccupied
            count=0;//reset the counters
            erasedcount =0;

    }
}

//hashing function
template<typename Type>
int Quadratic_hash_table<Type>::hashmap(const Type &obj) const{
    int hash_value = hash(obj) & mask;// creates a hashed index of the object to acess its hashed bin value
    return (hash_value >= 0) ? hash_value : hash_value + capacity();

}
// Your implementation here

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
