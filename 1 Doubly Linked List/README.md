### Project 1: Doubly Linked Sentinel List
\<Type\> templated linked list w/a second sentinel at the end (for improved indexing/insertion at the back of the list) and O(1) copy & move contructors.

**Project Description:**https://ece.uwaterloo.ca/~dwharder/aads/Projects/1/Double_sentinel_list/
Grade: 24/24 (100%)
  
##### Member Variables
- ```Double_Node list_head```
- ```Double_Node list tail```
- ```int list_size```
##### Accessors
- ```Double_sentinel_list<Type>::Double_node *begin() const```
- ```Double_sentinel_list<Type>::Double_node *end() const```
- ```Double_sentinel_list<Type>::Double_node *rbegin() const```
- ```Double_sentinel_list<Type>::Double_node *rend() const```
- ```Double_sentinel_list<Type>::Double_node find( Type const & ) const```
- ```int count( Type const & ) const```
- ```int size() const```
- ```bool empty() const```
- ```Type front() const```
- ```Type back() const```