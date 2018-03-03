/*****************************************
 * UW User ID:  uwuserid
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
#include "Double_sentinel_list.h"

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

        class iterator{
            public:
                Type &operator*();              //Overloaded dereference (returns node value)
                iterator operator++();
                iterator operator++(int);
                iterator operator--();
                iterator operator--(int);
                bool operator==(iterator const &) const;
                bool operator!=(iterator const &) const;

                friend class Double_sentinel_list<Type>;
            private:
//                iterator(Double_sentinel_list<Type>::Double_node*);
//                Double_sentinel_list::Double_node<Type>* current;       //Address of node currently being pointed to
        };

    private:
        int init_array_capacity;			//initial # of spots in array
        int array_capacity;					//current # of spots in array
        int deque_size;						//# items in array
        int ifront;							//index of first in array
        int	iback;							//index of last in array
        Type* array;	//Doubly linked list structure for queue/deque in place of contiguous array

        //Custom helper functions

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
        init_array_capacity(std::max(n, 16)),
        array_capacity(init_array_capacity),
        deque_size(0),
        ifront(0),
        iback(-1),
        array(new Type [init_array_capacity])
{
    for (int i = 0; i < init_array_capacity; i++){
        array->push_front(Type());
    }
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
// Your initalization list
{
    // Enter your implementation here
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
{
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
    delete array;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
    // Enter your implementation here
    return deque_size;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
    return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
    return deque_size == 0;
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
    return array->front();	//todo should be array[ifront]
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
    return array->back();	//todo should be array[iback]
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
    // Swap the member variables
    //     std::swap( variable, deque.variable );

    // Enter your implementation here
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
    // Enter your implementation here
}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
    if (deque_size == array_capacity) {
        throw overflow();
    }
    else
    {
        if (iback+1 == array_capacity) {	//if end of array is back of array use space at the front
            iback = 0;
        }else{
            ++iback;					//otherwise increment back of line normally
        }

        auto* ptr = array->begin();		//Double_sentinel_list::Double_node*
        for (int i = 0; i < iback; i++){
            ptr = ptr->next();
        }
        ptr->node_value = obj;

        ++deque_size;					//increment array size

    }
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
    if (empty()){
        throw underflow();
    }

    auto* ptr = array->begin();		//Double_sentinel_list::Double_node*
    for (int i = 0; i < ifront; i++){
        ptr = ptr->next();
    }
    ptr->node_value = 0;

    --deque_size;
    ++ifront;



}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
    // Enter your implementation here
}


template <typename Type>
void Resizable_deque<Type>::clear() {
    // Enter your implementation here
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
void set_val(Double_sentinel_list<Type>* list, int index, Type val){
    auto* ptr = list->begin();			//Double_sentinel_list::Double_node*
    for (int i = 0; i < index; i++){
        ptr = ptr->next();
    }
    ptr->node_value = val;
}

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &line ) {
    int i = 0;
    int val;

    for (auto ptr = line.array->begin(); ptr != line.array->end(); ptr = ptr->next()) {
        val = ptr -> value();

        //If front is also end and two digit value use '!' to represent '*' + '.'
        if (i == line.iback && i == line.ifront){
            if (val < 10){
                out << '*' << val << '.';
            }else{
                out << '!' <<val;
            }
        }
            //Mark array end w/ '.'
        else if (i == line.iback){
            if (val < 10){
                out << ' ' << val;
            }else{
                out << val;
            }
            out << '.';
        }
            //Mark array front w/ '*'
        else if( i == line.ifront){
            out << '*';
            if (val < 10){
                out << val << ' ';
            }else{
                out << val;
            }
        }
            //Stored values
        else if (val != 0){//should be empty/not empty nodes
            if (val < 10){
                out << ' ' << val << ' ';
            }else{
                out << val << ' ';
            }
        }
            //Blanks
        else{
            out << " _ ";
        }

        ++i;
    }
    return out << std::endl;
}

#endif
