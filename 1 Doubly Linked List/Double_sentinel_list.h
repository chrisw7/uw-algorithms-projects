/*****************************************
 * UW User ID:  cm3willi
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_head( new Double_node() ),                             //call default constructor for start sentinel
list_tail( new Double_node(Type(), list_head, nullptr) ),   //create end sentinel pointing to start sentinel
list_size( 0 )
{
	list_head->next_node = list_tail;                       //point start sentinel to end sentinel
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( new Double_node() ),
list_tail( new Double_node(Type(), list_head, nullptr)),
list_size( 0 )
{
    list_head->next_node = list_tail;                       //redundant? push_back should assign the sentinel next_node

    //push_back nodes associated with reference list after sentinel construction
    for (Double_node *ptr = list.begin(); ptr != list.end(); ptr = ptr->next() ){
        push_back(ptr->value());
    }
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    //Swap new null node with reference node;
    swap(list);
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    //Delete nodes associated with list on list delete
    int init_size = list_size;
    while (init_size > 0){
        pop_front();
        init_size--;
    }
    delete list_head;
    delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    //Return size of list
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    //Return whether or not list is empty (bool)
	return list_size == 0;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    //Return value of first node (after start sentinel)
    return begin()-> value();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    //Return value of last node (before end sentinel)
	return end()->previous()-> value();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
    //Returns address of first node after start sentinel
	return list_head->next_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
    //Returns address of end sentinel
	return list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    //Returns address of node before end sentinel
	return list_tail->previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	//Returns address of start sentinel
	return list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    //Iterate through list, return pointer to first node that has a value matching obj
    for (Double_node *ptr = begin(); ptr != list_tail; ptr = ptr->next()){
        if (ptr->value() == obj){
            return ptr;
        }
    }
    return end();
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    //Iterate through list incrementing counter for each node with value ==obj
    int counter = 0;
	for (Double_node *ptr = begin(); ptr != list_tail; ptr = ptr->next()){
        if (ptr->value() == obj){
            counter++;
        }
    }
    return counter;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	list_head->next_node = new Double_node(obj, list_head, begin());
    begin()->next()->previous_node = begin();
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    list_tail->previous_node = new Double_node(obj, end()->previous(), end());
    rbegin()->previous()->next_node = rbegin();
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
    if (empty()){
        throw underflow();                      //prevent user from popping empty list
    }

    Double_node *ptr = begin();                 //hold address of old first node
    begin()->next()->previous_node = list_head; //change following node to point to sentinel
    list_head->next_node = begin()->next();     //change sentinel to point to following node

    delete ptr;                                 //delete old node
    list_size--;                                //update list size
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    if (empty()){
        throw underflow();                      //prevent user from popping empty list
    }

    Double_node *ptr = rbegin();                //Re-route pointers (see pop_front)
    rbegin()->previous()->next_node = end();
    list_tail->previous_node = rbegin()->previous();

    delete ptr;                                 //delete old node
    list_size--;                                //update list size

}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    //Initialize tracking pointer and counting vars
    int init_count = count(obj);
    int remaining_nodes = init_count;
    Double_node *current_node = begin();

    //Iterate through list popping any nodes with value == obj
    while (remaining_nodes > 0){
        if (current_node->value() == obj){
            Double_node *ptr = current_node;                //Create temp ptr so delete doesn't break ptr->next()
            current_node = current_node->next();
            current_node->previous_node = ptr->previous();  //Re-assign next/previous addresses for surrounding nodes
            ptr->previous()->next_node = current_node;
            delete ptr;                                     //Delete node and update counters
            remaining_nodes--;
            list_size--;
        } else{
            current_node = current_node->next();
        }
    }
    return init_count;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
node_value( nv ),
previous_node( pn ),
next_node( nn )
{
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
