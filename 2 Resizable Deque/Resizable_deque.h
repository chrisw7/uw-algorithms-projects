/*****************************************
 * UW User ID:  cm3willi
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H
#include <algorithm>
#include "Exception.h"

template <typename Type>
class Resizable_deque {
public:
    Resizable_deque( int = 16 );
    Resizable_deque( Resizable_deque const & );
    Resizable_deque( Resizable_deque && );
    ~Resizable_deque();

    Type front() const;
    Type back() const;
    int size() const;
    bool empty() const;
    int capacity() const;

    void swap( Resizable_deque & );
    Resizable_deque &operator=( Resizable_deque const& );
    Resizable_deque &operator=( Resizable_deque && );
    void push_front( Type const & );
    void push_back( Type const & );
    void pop_front();
    void pop_back();
    void clear();

private:
    int init_array_capacity;			//initial # of spots in array
    int array_capacity;					//current # of spots in array
    int deque_size;						//# items in array
    int ifront;							//index of first in array
    int	iback;							//index of last in array
    Type* array;                        //Array structure

    bool full();                        //check if size = capacity
    void resize_array();                //reshape array dynamically

    // Friends

    template <typename T>
    friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n ):
        init_array_capacity(std::max(n, 16)),   //min array size 16
        array_capacity(init_array_capacity),
        deque_size(0),
        ifront(0),                              //set front index to [0]
        iback(-1),                              //set back index out of bounds
        array(new Type [array_capacity])        //allocate array on heap
{
    /*for (int i = 0; i < array_capacity; i++){
        array[i] = 0;
    }*/
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque ):
        init_array_capacity(deque.init_array_capacity),
        array_capacity(deque.array_capacity),
        deque_size(deque.deque_size),
        ifront(deque.ifront),
        iback(deque.iback),
        array(new Type [array_capacity])
{
    for (int i = 0; i < array_capacity; i++){
        array[i] = deque.array[i];              //element-by-element copy
    }
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque ):
        init_array_capacity(0),
        array_capacity(0),
        deque_size(0),
        ifront(0),
        iback(0),
        array(nullptr)
{
    swap(deque);                                //swap input array with null object
}

// Destructor;
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
    delete [] array;;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {       //Deque Size
    return deque_size;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {   //Current capacity
    return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {     //Check to see if deque is empty
    return deque_size == 0;
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {     //Return value at front of line; throw underflow if empty
    return empty() ? throw underflow() : array[ifront];
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {      //Return value at back of line; throw underflow if empty

    return empty() ? throw underflow() : array[iback];
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
    // Swap the member variables
    std::swap(init_array_capacity, deque.init_array_capacity );
    std::swap(array_capacity, deque.array_capacity );
    std::swap(deque_size, deque.deque_size );
    std::swap(ifront, deque.ifront );
    std::swap(iback, deque.iback );
    //Swap array
    std::swap(array, deque.array );
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
    // This is done for you...
    Resizable_deque<Type> copy( rhs );
    swap( copy );

    return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
    // This is done for you...
    swap( rhs );

    return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
    if (full()) {
        resize_array();                     //double array capacity and reload elements if full
    }

    if (deque_size != 0) {                  //if array isn't empty shift front of line
        if (ifront == 0){
            ifront = array_capacity -1;     //circular push
        }else{
            --ifront;
        }
    }else{
        ++iback;                            //change iback from -1 to 0 so that front() == back()
    }

    array[ifront] = obj;
    ++deque_size;                           //increment array size

}


template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
    if (full()) {
        resize_array();                 //double array capacity and reload elements if full
    }
    if (iback == array_capacity-1) {	//if end of array is back of array use space at the front
        iback = 0;
    }else{
        ++iback;					    //otherwise increment back of line normally
    }

    array[iback] = obj;
    ++deque_size;					    //increment array size


}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
    //Catch empty pop
    if (empty()){
        throw underflow();
    }

    //Shift front of line
//    array[ifront] = 0;                  //todo: not necessary
    if (ifront < array_capacity-1){
        ++ifront;
    }else{
        ifront = 0;                     //circular pop
    }

    //Update line size
    --deque_size;

    if(size() == capacity()/4 && capacity() > init_array_capacity){
        resize_array();                 //downsize array and reload if 3/4 empty
    }
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
    //Catch empty pop
    if (empty()){
        throw underflow();
    }

    //Shift front of line
//    array[iback] = 0;                  //todo not necessary
    if (iback > 0){
        --iback;
    }else{
        iback = array_capacity-1;      //circular pop
    }

    //Update line size
    --deque_size;

    if(size() == capacity()/4 && capacity() > init_array_capacity){
        resize_array();             //downsize array and reload if 3/4 empty
    }
}


template <typename Type>
void Resizable_deque<Type>::clear() {
    array_capacity = init_array_capacity;
    deque_size = 0;
    ifront = 0;
    iback = -1;

    auto ptr = array;
    array = new Type[init_array_capacity];                      //reset array to initial size
    /*for (int k = 0; k < capacity(); k++){                     //todo - remove this (fills new array with zeros)
        array[k] = 0;
    }*/
    delete [] ptr;
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

template <typename  Type>
bool Resizable_deque<Type>::full(){                         //Check if array size has reached capacity
    return size() == capacity();
}

template <typename Type>
void Resizable_deque<Type>::resize_array(){
    //Initialize variables
    auto ptr = array;                                       //Save ptr to old array in prep for deletion
    int old_size = capacity();                              //store array_capacity with a single call of capacity()
    int i = ifront-1;                                       //initialize counters, compensate for initial ++
    int j = -1;

    array_capacity = full() ? capacity()*2 : capacity()/2;  //update capacity
    Type *new_deque = new Type[array_capacity];             //heap allocate array with *new* capacity

/*    for (int k = 0; k < capacity(); k++){                   //todo - remove this (fill new array with zeros
        new_deque[k] = 0;
    }*/

    //Iterate through old circular array filling new array starting from index [0]
    do{
        ++i;
        ++j;
        if (i == old_size) i=0;
        new_deque[j] = array[i];
    }while(i != iback);

    //Update member variables, free memory for old array
    ifront = 0;
    iback  = size()-1;
    array = new_deque;
    delete [] ptr;

}

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &line ) {
    int i = 0;
    int val;

    for (int i = 0; i < line.capacity(); i++) {
        val = line.array[i];

        //If front is also end and two digit value use '!' to represent '*' + '.'
        if (i == line.iback && i == line.ifront){
            if (val < 10 && val > 0){
                out << '*' << val << '.';
            }else if(val == 0){
                out << '*' << '_' << '.';
            }else{
                out << '!' <<val;
            }
        }
            //Mark array end w/ '.'
        else if (i == line.iback){
            if (val < 10 && val > 0){
                out << ' ' << val;
            }else if(val == 0){
                out << '_' << ' ';
            }else{
                out << val;
            }
            out << '.';
        }
            //Mark array front w/ '*'
        else if( i == line.ifront){
            out << '*';
            if (val < 10 && val > 0){
                out << val << ' ';
            }else if(val == 0){
                out << '_' << ' ';
            }else{
                out << val;
            }
        }
            //Stored values
        else if (val != 0){//should be empty/not empty nodes
            if (val < 10){
                out << ' ' << val << ' ';
            }else{
                out << ' ' << val;
            }
        }
            //Blanks
        else{
            out << " _ ";
        }

    }
    return out << std::endl;
}

#endif
