## Project 1: [Doubly Linked Sentinel List](<1 Doubly Linked List/>)

| Complete?	| Description 	| Grade |
| :---: 			| :--- 			| --- 	|
| :heavy_check_mark: | \<Type\> templated linked list w/a second sentinel at the end (for improved indexing/insertion at the back of the list) and O(1) copy & move constructors| | **24/24** (100%) |
**Full Description:**https://ece.uwaterloo.ca/~dwharder/aads/Projects/1/Double_sentinel_list/
  
##### Member Variables
- ```Double_Node list_head```
- ```Double_Node list tail```
- ```int list_size```

##### Accessors
- ```Double_sentinel_list<Type>::Double_node *begin() const```
	- Returns the address stored by the next pointer of the head sentinel node. (O(1))
- ```Double_sentinel_list<Type>::Double_node *end() const```
	- Returns the address of the tail sentinel node. (O(1))
- ```Double_sentinel_list<Type>::Double_node *rbegin() const```
	- Returns the address stored by the previous pointer of the tail sentinel node. (O(1))
- ```Double_sentinel_list<Type>::Double_node *rend() const```
	- Returns the address of the head sentinel node. (O(1))
- ```Double_sentinel_list<Type>::Double_node find( Type const & ) const```
	- Returns the address of the first node in the linked list storing a value equal to the argument; if none is found, return end(). (O(n))
- ```int count( Type const & ) const```
	- Returns the number of nodes in the linked list storing a value equal to the argument. (O(n))
- ```int size() const```
	- Returns the number of items in the list. (O(1))
- ```bool empty() const```
	- Returns true if the list is empty, false otherwise. (O(1))
- ```Type front() const```
	- Retrieves the object stored in the node pointed to by the next pointer of the head sentinel. This function throws a underflow if the list is empty. (O(1))
- ```Type back() const```
	- Retrieves the object stored in the node pointed to by the previous pointer of the tail sentinel. This function throws a underflow if the list is empty. (O(1))
\<Type\> templated linked list w/a second sentinel at the end (for improved indexing/insertion at the back of the list) and O(1) copy & move constructors
