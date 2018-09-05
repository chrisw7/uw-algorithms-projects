## Linked Lists

A linear data structure consisting of a set of nodes typically containing data and a reference adress pointing to the next node in memory

- Pros: Simple, O(1) insertions w/out reallocation
- Cons: Inefficient Indexing, poor cache locality

### Project 1: [Doubly Linked Sentinel List](https://ece.uwaterloo.ca/~dwharder/aads/Projects/1/Double_sentinel_list/) (24/24)
\<Type\> templated linked list w/a second sentinel at the end (for improved indexing/insertion at the back of the list) and O(1) copy & move contructors.
  
##### Member Variables
- ```Double_Node list_head```
- ```Double_Node list tail```
- ```int list_size```
##### const Accessors
- ```Double_sentinel_list<Type>::Double_node *begin()```
- ```Double_sentinel_list<Type>::Double_node *end()```
- ```Double_sentinel_list<Type>::Double_node *rbegin()```
- ```Double_sentinel_list<Type>::Double_node *rend()```
- ```Double_sentinel_list<Type>::Double_node find( Type const & )```
- ```int count( Type const & )```
- ```int size()```
- ```bool empty()```
- ```Type front()```
- ```Type back()```
