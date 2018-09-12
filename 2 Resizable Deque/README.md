### Project 2: Resizable Deque
 <Type> templated circular array implementation of a resizable deque structure. Capacity of dynamic array is doubled when push is called in a deque overflow state resulting in amortized. O(1) push operations.

**Full Project Description:** https://ece.uwaterloo.ca/~dwharder/aads/Projects/2/Resizable_deque/
Grade: 28/28 (100%)
  
##### Accessors
- ```Type front() const```
 - Return the object at the front of the deque. It may throw a underflow exception. (O(1))
- ```Type back() const```
 - Return the object at the back of the deque. It may throw a underflow exception. (O(1))
- ```int size() const```
 - Returns the number of elements currently stored in the deque. (O(1))
- ```bool empty() const```
 - Returns true if the deque is empty, false otherwise. (O(1))
- ```int capacity() const```
 - Returns the current capacity of the array. (O(1))

##### Mutators
- ```void swap( Resizable_deque & )```
 - The swap function swaps all the member variables of this deque with those of the argument. (O(1))
- ```Resizable_deque &operator=( Resizable_deque const & )```
 - The assignment operator makes a copy of the argument and then swaps the member variables of this node with those of the copy. (O(max{nlhs, nrhs}))
- ```Resizable_deque &operator=( Resizable_deque &&rhs )```
 - The move operator moves the array in the argument (the right-hand side of the assignment) linked list to this linked list, changing the argument linked list into an empty list. (O(1))
- ```void push_front( Type const & )```
 - Insert the new element at the front of the deque. If before the element is placed into the deque, the array is filled, the capacity of the array is doubled. (O(1) on average)
- ```void push_back( Type const & )```
 - Insert the new element at the back of the deque. If before the element is placed into the deque, the array is filled, the capacity of the array is doubled. (O(1) on average)
- ```void pop_front()```
 - Removes the element at the front of the deque. If, after the element is removed, the array is 1/4 full or less and the array capacity is greater than the initial capacity, the capacity of the array is halved. This may throw a underflow exception. (O(1) on average)\
- ```void pop_back()```
 - Removes the element at the back of the deque. If, after the element is removed, the array is 1/4 full or less and the array capacity is greater than the initial capacity, the capacity of the array is halved. This may throw a underflow exception. (O(1) on average)
- ```void clear()```
 - Empties the deque by resetting the member variables. The array is resized to the initial capacity. (O(1))
