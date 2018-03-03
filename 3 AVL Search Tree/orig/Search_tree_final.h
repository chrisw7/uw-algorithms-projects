/*****************************************
 * UW User ID:  cm3willi
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef RPOVDGBQN9TIEO3P
#define RPOVDGBQN9TIEO3P

#include "Exception.h"
#include "ece250.h"
#include <cassert>
#include <algorithm>

template <typename Type>
class Search_tree {
	public:
		class Iterator;

	private:
		class Node {
			public:
				Type node_value;
				int tree_height;

				// The left and right sub-trees
				Node *left_tree;
				Node *right_tree;

				// Hint as to how you can create your iterator
				// Point to the previous and next nodes in linear order
				Node *previous_node;
				Node *next_node;

				// Member functions
				Node( Type const & = Type() );

				void update_height();

				int height() const;
				bool is_leaf() const;
				Node *front();
				Node *back();
				Node *find( Type const &obj );

				void clear();
				bool insert( Type const &obj, Node *&to_this );
				bool erase( Type const &obj, Node *&to_this );

		};

		Node *root_node;
		int tree_size;

		// Hint as to how to start your linked list of the nodes in order
		Node *front_sentinel;
		Node *back_sentinel;

	public:
		class Iterator {
			private:
				Search_tree *containing_tree;
				Node *current_node;
				bool is_end;

				// The constructor is private so that only the search tree can create an iterator
				Iterator( Search_tree *tree, Node *starting_node );

			public:
				// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
				Type operator*() const;
				Iterator &operator++();
				Iterator &operator--();
				bool operator==( Iterator const &rhs ) const;
				bool operator!=( Iterator const &rhs ) const;

			// Make the search tree a friend so that it can call the constructor
			friend class Search_tree;
		};

		// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
		Search_tree();
		~Search_tree();

		bool empty() const;
		int size() const;
		int height() const;

		Type front() const;
		Type back() const;

		Iterator begin();
		Iterator end();
		Iterator rbegin();
		Iterator rend();
		Iterator find( Type const & );

		void clear();
		bool insert( Type const & );
		bool erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Search_tree<T> const & );
};

//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////

// The initialization of the front and back sentinels is a hint
template <typename Type>
Search_tree<Type>::Search_tree():
root_node( nullptr ),
tree_size( 0 ),
front_sentinel( new Search_tree::Node( Type() ) ),
back_sentinel( new Search_tree::Node( Type() ) ) {
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
Search_tree<Type>::~Search_tree() {
	clear();  // might as well use it...
	delete front_sentinel;
	delete back_sentinel;
}

template <typename Type>
bool Search_tree<Type>::empty() const {
	return ( root_node == nullptr );
}

template <typename Type>
int Search_tree<Type>::size() const {
	return tree_size;
}

template <typename Type>
int Search_tree<Type>::height() const {
	return root_node->height();
}

template <typename Type>
Type Search_tree<Type>::front() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->front()->node_value;
}

template <typename Type>
Type Search_tree<Type>::back() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->back()->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::begin() {
	return empty() ? Iterator( this, back_sentinel ) : Iterator( this, root_node->front() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::end() {
	return Iterator( this, back_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rbegin() {
	return empty() ? Iterator( this, front_sentinel ) : Iterator( this, root_node->back() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rend() {
	return Iterator( this, front_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::find( Type const &obj ) {
	if ( empty() ) {
		return Iterator( this, back_sentinel );
	}

	typename Search_tree<Type>::Node *search_result = root_node->find( obj );

	if ( search_result == nullptr ) {
		return Iterator( this, back_sentinel );
	} else {
		return Iterator( this, search_result );
	}
}

template <typename Type>
void Search_tree<Type>::clear() {
	if ( !empty() ) {
		root_node->clear();
		root_node = nullptr;
		tree_size = 0;
	}

	// Reinitialize the sentinels
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
bool Search_tree<Type>::insert( Type const &obj ) {
	if ( empty() ) {
		root_node = new Search_tree::Node( obj );
		tree_size = 1;
		root_node->next_node = back_sentinel;
		root_node->previous_node = front_sentinel;
		back_sentinel->previous_node = root_node;
		front_sentinel->next_node = root_node;
		return true;
	} else if ( root_node->insert( obj, root_node ) ) {
		++tree_size;

		return true;
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::erase( Type const &obj ) {
	if ( !empty() && root_node->erase( obj, root_node ) ) {
		--tree_size;
		return true;
	} else {
		return false;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Node::Node( Type const &obj ):
node_value( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
next_node( nullptr ),
previous_node( nullptr ),
tree_height( 0 ) {
	// does nothing
}

template <typename Type>
void Search_tree<Type>::Node::update_height() {
	tree_height = std::max( left_tree->height(), right_tree->height() ) + 1;
}

template <typename Type>
int Search_tree<Type>::Node::height() const {
	return ( this == nullptr ) ? -1 : tree_height;
}

// Return true if the current node is a leaf node, false otherwise
template <typename Type>
bool Search_tree<Type>::Node::is_leaf() const {
	return ( (left_tree == nullptr) && (right_tree == nullptr) );
}

// Return a pointer to the front node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::front() {
	return ( left_tree == nullptr ) ? this : left_tree->front();
}

// Return a pointer to the back node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::back() {
	return ( right_tree == nullptr ) ? this : right_tree->back();
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::find( Type const &obj ) {
	if ( obj == node_value ) {
		return this;
	} else if ( obj < node_value ) {
		return (left_tree == nullptr) ? nullptr : left_tree->find( obj );
	} else {
		return (right_tree == nullptr) ? nullptr : right_tree->find( obj );
	}
}

// Recursively clear the tree
template <typename Type>
void Search_tree<Type>::Node::clear() {
	if ( left_tree != nullptr ) {
		left_tree->clear();
	}

	if ( right_tree != nullptr ) {
		right_tree->clear();
	}

	delete this;
}

template <typename Type>
bool Search_tree<Type>::Node::insert( Type const &obj, Search_tree<Type>::Node *&to_this) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
            //Create new node on heap in left tree
			left_tree = new Search_tree<Type>::Node( obj );
			//Update tree_height to reflect new node
            update_height();

            //Track linear order upon insertion for iterator
            left_tree->next_node = this;					//tell new node its next node is its parent
			left_tree->previous_node = this->previous_node;	//tell new node its previous node was the node before its parent
			previous_node->next_node = left_tree;
			previous_node = left_tree;						//tell current node its previous node has been updated
			return true;

		} else {
            //Recursively traverse tree until space for new node is found
			if (left_tree->insert(obj, left_tree )) {

                if (left_tree->height() - right_tree ->height() == 2){
                    //Left-Left insertion
                    if (obj < left_tree->node_value){
                        //Create local pointers to the node to be promoted and the old right tree
                        auto *new_root = left_tree;
                        auto *old_rtree = new_root->right_tree;

                        //Promote middle node and reassign *this and old_rtree as children
                        new_root->right_tree = this;
                        to_this = new_root;
                        left_tree = old_rtree;

                        //Update height now that subtree is balanced
                        update_height();
                    }
                    //Left-Right insertion
                    else if(left_tree->node_value < obj < this->node_value){ //Left-Right
                        //Create local pointers to the node to be promoted and its subtrees to-be
                        auto *old_ltree = left_tree;
                        auto *new_root = old_ltree->right_tree;
                        auto *l_subtree =  new_root->left_tree;
                        auto *r_subtree = new_root->right_tree;

                        //Promote middle node and reassign subtrees and *this
                        new_root->left_tree = old_ltree;
                        new_root->right_tree = this;
                        to_this = new_root;
                        old_ltree->right_tree = l_subtree;
                        left_tree = r_subtree;

                        //Update heights for nodes in new positions
                        update_height();
                        old_ltree->update_height();
                        new_root->update_height();
                    }
                }else{
                    //If balanced simply update height to reflect new insertion
                    update_height();
                }

				return true;
			} else {
				return false;
			}
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
            //Create new node on heap
			right_tree = new Search_tree<Type>::Node( obj );
			update_height();

            //Track linear order upon insertion
            right_tree->previous_node = this;
			right_tree->next_node = this->next_node;
			next_node->previous_node = right_tree;
			next_node = right_tree;
			return true;

		} else {
            //Recursive insertion
			if ( right_tree->insert( obj, right_tree ) ) {
                if (left_tree->height() - right_tree ->height() == -2) {
                    //Symmetric to left-x cases; swap all rights for lefts
                    //Right-Right insertion
                    if (obj > right_tree->node_value) {
                        //Initialize
                        auto *new_root = right_tree;
                        auto *old_ltree = new_root->left_tree;

                        //Re-assign
                        new_root->left_tree = this;
                        to_this = new_root;
                        right_tree = old_ltree;

                        //Reflect height changes
                        update_height();

                        //Right-left insertion
                    } else if (obj < right_tree->node_value) {
                        //Initialize
                        auto *old_rtree = right_tree;
                        auto *new_root = old_rtree->left_tree;
                        auto *l_subtree = new_root->left_tree;
                        auto *r_subtree = new_root->right_tree;

                        //Re-assign
                        new_root->right_tree = old_rtree;
                        new_root->left_tree = this;
                        to_this = new_root;
                        old_rtree->left_tree = r_subtree;
                        right_tree = l_subtree;

                        //Reflect height changes
                        update_height();
                        old_rtree->update_height();
                        new_root->update_height();
                    }
                }else{
                    update_height();
                }

				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::Node::erase( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			return false;
		} else {
			if ( left_tree->erase( obj, left_tree ) ) {
                if (left_tree->height() - right_tree ->height() == 2){
                    //Left-Left deletion
                    if ( (left_tree->left_tree->height() - left_tree->right_tree->height()) >=0){
                        //Create local pointers to the node to be promoted and the old right tree
                        auto *new_root = left_tree;
                        auto *old_rtree = new_root->right_tree;

                        //Promote middle node and reassign *this and old_rtree as children
                        new_root->right_tree = this;
                        to_this = new_root;
                        left_tree = old_rtree;

                        //Update height now that subtree is balanced
                        update_height();
                    }
                    //Left-Right deletion
                    else if( (left_tree->left_tree->height() < left_tree->right_tree->height()) ){
                        //Create local pointers to the node to be promoted and its subtrees to-be
                        auto *old_ltree = left_tree;
                        auto *new_root = old_ltree->right_tree;
                        auto *l_subtree =  new_root->left_tree;
                        auto *r_subtree = new_root->right_tree;

                        //Promote middle node and reassign subtrees and *this
                        new_root->left_tree = old_ltree;
                        new_root->right_tree = this;
                        to_this = new_root;
                        old_ltree->right_tree = l_subtree;
                        left_tree = r_subtree;

                        //Update heights for nodes in new positions
                        update_height();
                        old_ltree->update_height();
                        new_root->update_height();
                    }
                }else if(left_tree->height() - right_tree ->height() == -2){
                    //Symmetric to left-x cases; swap all rights for lefts
                    //Right-Right deletion
                    if ( (right_tree->left_tree->height() - right_tree->right_tree->height()) <= 0) {
                        //Initialize
                        auto *new_root = right_tree;
                        auto *old_ltree = new_root->left_tree;

                        //Re-assign
                        new_root->left_tree = this;
                        to_this = new_root;
                        right_tree = old_ltree;

                        //Reflect height changes
                        update_height();

                        //Right-left deletion
                    } else if (right_tree->left_tree->height() > right_tree->right_tree->height()) {
                        //Initialize
                        auto *old_rtree = right_tree;
                        auto *new_root = old_rtree->left_tree;
                        auto *l_subtree = new_root->left_tree;
                        auto *r_subtree = new_root->right_tree;

                        //Re-assign
                        new_root->right_tree = old_rtree;
                        new_root->left_tree = this;
                        to_this = new_root;
                        old_rtree->left_tree = r_subtree;
                        right_tree = l_subtree;

                        //Reflect height changes
                        update_height();
                        old_rtree->update_height();
                        new_root->update_height();
                    }
                }
                //check Right-X imbalances too
                else{
                    //If balanced simply update height to reflect new insertion
                    update_height();
                }
				return true;
			}

			return false;
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			return false;
		} else {
			if ( right_tree->erase( obj, right_tree ) ) {
                if (left_tree->height() - right_tree ->height() == 2){
                    //Left-Left deletion
                    if ( (left_tree->left_tree->height() - left_tree->right_tree->height()) >=0){
                        //Create local pointers to the node to be promoted and the old right tree
                        auto *new_root = left_tree;
                        auto *old_rtree = new_root->right_tree;

                        //Promote middle node and reassign *this and old_rtree as children
                        new_root->right_tree = this;
                        to_this = new_root;
                        left_tree = old_rtree;

                        //Update height now that subtree is balanced
                        update_height();
                    }
                        //Left-Right deletion
                    else if( (left_tree->left_tree->height() < left_tree->right_tree->height()) ){
                        //Create local pointers to the node to be promoted and its subtrees to-be
                        auto *old_ltree = left_tree;
                        auto *new_root = old_ltree->right_tree;
                        auto *l_subtree =  new_root->left_tree;
                        auto *r_subtree = new_root->right_tree;

                        //Promote middle node and reassign subtrees and *this
                        new_root->left_tree = old_ltree;
                        new_root->right_tree = this;
                        to_this = new_root;
                        old_ltree->right_tree = l_subtree;
                        left_tree = r_subtree;

                        //Update heights for nodes in new positions
                        update_height();
                        old_ltree->update_height();
                        new_root->update_height();
                    }
                }else if(left_tree->height() - right_tree ->height() == -2){
                    //Symmetric to left-x cases; swap all rights for lefts
                    //Right-Right insertion
                    if ( (right_tree->left_tree->height() - right_tree->right_tree->height()) <= 0) {
                        //Initialize
                        auto *new_root = right_tree;
                        auto *old_ltree = new_root->left_tree;

                        //Re-assign
                        new_root->left_tree = this;
                        to_this = new_root;
                        right_tree = old_ltree;

                        //Reflect height changes
                        update_height();

                        //Right-left insertion
                    } else if (right_tree->left_tree->height() > right_tree->right_tree->height()) {
                        //Initialize
                        auto *old_rtree = right_tree;
                        auto *new_root = old_rtree->left_tree;
                        auto *l_subtree = new_root->left_tree;
                        auto *r_subtree = new_root->right_tree;

                        //Re-assign
                        new_root->right_tree = old_rtree;
                        new_root->left_tree = this;
                        to_this = new_root;
                        old_rtree->left_tree = r_subtree;
                        right_tree = l_subtree;

                        //Reflect height changes
                        update_height();
                        old_rtree->update_height();
                        new_root->update_height();
                    }
                }
                //check Right-X imbalances too
                else{
                    //If balanced simply update height to reflect new insertion
                    update_height();
                }
                return true;
			}

			return false;
		}
	} else {
		assert( obj == node_value );
        //Delete nodes from tree
		if ( is_leaf() ) {
            //Update linked list
            next_node->previous_node = previous_node;
            previous_node->next_node = next_node;
			to_this = nullptr;
			delete this;
		} else if ( left_tree == nullptr ) {
            //Update linked list
            next_node->previous_node = previous_node;
            previous_node->next_node = next_node;
			to_this = right_tree;
			delete this;
		} else if ( right_tree == nullptr ) {
            //Update linked list
            next_node->previous_node = previous_node;
            previous_node->next_node = next_node;
			to_this = left_tree;
			delete this;
		} else {
            //Update linked list
			node_value = right_tree->front()->node_value;
			right_tree->erase( node_value, right_tree );
			update_height();
		}
		return true;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Iterator::Iterator( Search_tree<Type> *tree, typename Search_tree<Type>::Node *starting_node ):
containing_tree( tree ),
current_node( starting_node ) {
	// This is done for you...
	// Does nothing...
}

//////////////////////////////////////////////////////////////////////
//                 Iterator Public Member Functions                 //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Type Search_tree<Type>::Iterator::operator*() const {
	// This is done for you...
	return current_node->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator++() {
	// Update the current node to the node containing the next higher value
	// If we are already at end do nothing
    if (current_node != containing_tree->end().current_node){    //todo check endstops, add is_end update
        current_node = current_node->next_node;
    }

	return *this;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator--() {
	// Update the current node to the node containing the next smaller value
	// If we are already at either rend, do nothing

    if (current_node != containing_tree->rend().current_node){
        current_node = current_node->previous_node;
    }
	return *this;
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator==( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node == rhs.current_node );
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator!=( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node != rhs.current_node );
}

//////////////////////////////////////////////////////////////////////
//                            Friends                               //
//////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Search_tree<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
