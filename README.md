# [ECE 250 - Data Structures & Algorithms](https://ece.uwaterloo.ca/~dwharder/aads/Outline/)

**Course Objectives**

> Introduce the student to the concept of data structures through abstract data structures including lists, sorted lists, stacks, queues, deques, sets/maps, directed acyclic graphs, and graphs; and implementations including the use of linked lists, arrays, binary search trees, M-way search trees, hash tables, complete trees, and adjacency matrices and lists.

> Introduce the student to algorithms design including greedy, divide-and-conquer, random and backtracking algorithms and dynamic programming; and specific algorithms including, for example, resizing arrays, balancing search trees, shortest path, and spanning trees.

---
## Background

Data structures & algorithms govern the way we interact with digital information. At the highest level, they are used to organize and access abstract data types like containers (which store collections of objects).

### Relationships & Orderings
The relationship between objects is often just as important as the information stored in the object. Most data structures can be described using the following six relationships:
 
| Relationship 			| Description	| Examples |
| --- 					| ----- 			| ---- |
| Linear order			| Every object is strictly less than, equal to, or greater than another and vice versa (transitive) | Integers, hexadecimal memory addresses, alphabet
| Hierarchical order	| Each object has a *parent* object with the exception of a singular *root* object |  Unix directories, class inheritance in C# and Java
| Partial order			| A hierarchical ordering with 1 or more root and no loops |  C++ classes (multiple inheritance), compilation dependencies
| Equivalence relation	| Relationships where objects can be partitioned into subsets (equivalence relations) with other 'weakly' related (x~y) objects |  Landau symbol *Ө* `2n ~ 5n ∈ Ө(n)`
| Weak order			| A linear ordering of equivalence classes |  Big-O notation `O(1)`< `O(ln(n))` < `O(n·ln(n))` 
| Adjacency relation	| Relationships described by one object being connected to another (x ↔ y) |  Graphs, social networks
  
### Asymptotic Analysis & Big-O Notation
It's often useful to analyze and compare algorithms with respect to one or more variables (i.e. run-time, memory). Using the same 'Big O' mathematical notation and Landau symbols used to describe the limiting behaviour of a function, the efficiency of different algorithms can be compared. For two algorithms described by the functions `f(n)` and `g(n)`, the best- and worst-case behaviour of the algorithms  can be described as such (*n* can be a measure of run-time or memory):

- `f(n) = o(g(n))` when `f(n)` approaches ∞ at a slower rate than `g(n)` (**f outperforms g**)
- `f(n) = O(g(n))` when `f(n)` approaches ∞ at a rate equal to or slower than `g(n)` (**f, at *worst*, performs the same g**)
- `f(n) = Ω(g(n))` when `f(n)` approaches ∞ at a rate equal to or faster than`g(n)` (**f, at *best*, performs the same g**)
- `f(n) = ω(g(n))` when `f(n)` approaches ∞ at a much slower rate than `g(n)` (**g outperforms f**)
- `f(n) = Ө(g(n))` when `f(n)` and `g(n)` approach ∞ at comparable rates (**f and g perform roughly the same**)

<p align="center"><img src="img/big-O.png"/></p>

Note that since this notation describes limiting behaviour, one should be wary of making objective statements about the relative performance of two different algorithms without context. For example, even though f may run faster than g for n = 1000000, the opposite could be true when the same algorithms are run on only 1000 objects. Similarly, since Big-O notation gives information about the relative scaling and complexity of different algorithms rather than their absolute performance, for an algorithm f that scales faster than another, g, by a constant factor, `f(n) = Ө(g(n))` is still true.

After taking these caveats into consideration, Landau symbols prove very useful for describing the complexity of an algorithm. An algorithm is considered to run in *polynomial time* if its run time can be described by `O(n^d)` for d greater than or equal to zero. Algorithms with polynomial time complexity are considered efficient in the current non-quantum state of computing, whereas problems that can not be solved in polynomial time are considered intractable or infeasible (e.g. the traveling salesman problem with complexity `O(n<sup>2</sup>2<sup>n</sup>) at best)`. Although these problems could still theoretically be solved, the scaling is computationally inefficient enough that it is typically not worth the effort except for special cases of the problem.

<p align="center"><img src="img/little-o.png"/></p>

---
## Linked Lists

Linked lists are the simplest type of data structure, consisting of a set of linearly ordered nodes that, in addition to storing data, also contain an address pointing to the location next node in memory.

<p align="center"><img src="img/linked-list.png"/></p>

- Pros: Simple, `O(1)` insertions w/out reallocation
- Cons: Inefficient indexing, poor cache locality

>#### Project 1: [Doubly Linked Sentinel List](<1 Doubly Linked List/>)
>| Complete?	| Description 	| Grade |
>| :---: 			| :--- 			| --- 	|
>| :heavy_check_mark: | \<Type\> templated linked list w/a second sentinel at the end (for improved indexing/insertion at the back of the list) and O(1) copy & move constructors | **24/24** (100%) |

---
## Stacks , Queues, & Deques

The stack data structure are most commonly used as data buffers. Being linearly ordered, stacks are often implemented using a wrapper class around a linked list, and as such retain much of the functionality of a list structure. However, rather than manually traversing the list, member functions for stack/buffer data structures are typically limited to two principal operations that insert (`push`) and remove (`pop`) an object onto/from the stack.

Traditional stacks display last-in-first-out (LIFO) behaviour meaning the first object pushed onto the stack cannot be popped until all of the objects pushed after it have been popped -  like a stack of books. Stacks with a first-in-first-out (FIFO) behaviour are called queues (for reasons that should be self-evident). Apart from the obvious applications (waiting in line at the bank), queues more generally used in client-server models where the server must handle a large number of service requests from clients. Finally, the deque abstract data structure allows an objects to be pushed to the front or the back of the list meaning it can be used as either a queue or a stack.

### Other Considerations

Despite being a relatively simple data structure, efforts to optimize the efficiency of real-life implementations can be very complicated. For example, stacks and queues can also be implemented efficiently using dynamic arrays. Whereas prepending to a linked list is always `O(1)`, appending elements to an array list is *amortized* `O(1)` meaning although the total time for n insertions is `O(n)`, the time bound of any individual insertions can be much worse. This is a result of the cost of resizing a full array and reallocating contiguous blocks of memory. Conversely, unlike linked lists which usually require `O(n)` memory to store pointers in each node, the memory overhead for a dynamic array is typically `O(1)` (only approaching `O(n)` after the array capacity is doubled). Other examples of stack-based structure implementations include queues with dynamic array used as a circular buffer, priority queues, and other more esoteric structures like hybrid VLists.

<p align="center"><img src="img/deque.png"/></p>

>#### Project 2: [Resizable Deque](<2 Resizable Deque/>)
>| Complete? 			| Description 	| Grade |
>| :---: 				| :--- 			| --- 	|
>| :heavy_check_mark: 	| \<Type\> templated circular array implementation of a resizable deque structure. Capacity of dynamic array is doubled when push is called in a deque overflow state resulting in amortized. O(1) push operations | **28/28** (100%) |
---
## Trees

Perhaps one of the most widely used and versatile data structures is the hierarchically-ordered tree structure consisting of a *root* node (with no superior) and subtrees of *children* that succeed it (each with a superior *parent* node). The *degree* of an individual node refers to the number of children succeeding that node, with a node with degree zero referred to as a leaf node. There exists a unique path from each node in a tree from the root node to that node, the length of which is referred to as the *depth* of the node. The *height* of a tree is defined as the maximum depth of any node in the tree. Like stacks, tree data structures can be implemented using a collection of linked lists (with nodes containing addresses of the parent node and its children), or by cleverly taking advantage of the contiguous memory allocation of arrays. Traversing these trees in order is typically accomplished using a stack (breadth-first) or using recursion (depth-first).

### *N*-ary trees
An *N*-ary tree is a tree with each node containing at most *N* sub-trees. Each node of a binary search tree, for example, contains at most two children normally referred to as the 'left' and 'right' child. In a 'perfect' *N*-ary tree, every node has exactly two children except for the nodes at the maximum depth (bottom layer) of the tree which are leaf nodes (with no children). A 'complete' *N*-ary on the other hand, must be filled from left to right meaning the tree is perfect except for the leaf nodes a the deepest level (which may or may not be filled).

A perfect *N*-ary tree with height h will by definition always contain n=(*N*<sup>h+1</sup>-1) / (*N*-1) nodes, which for a binary tree simplifies to 2<sup>h+1</sup>-1 nodes. Rearranging for the height, h we find h= log<sub>*N*</sub>(n(*N*-1)+1)-1 which is typically approximated as h =~ log<sub>*N*</sub>(n). This proves important for run-time analyses of operations on trees, which are usually `O(h)`. For example, because order is preserved in complete binary trees, they can be used to store sorted lists where every node of a left sub-tree contains elements strictly smaller than the root element, and every node of a right sub-tree contains elements strictly greater than the root element (known as a binary search tree). Unlike arrays and other sorted list structures with `O(n)` operations, finding and inserting elements in a binary search trees only requires an `O(h)` depth-first (recursive) traversal of the tree. Note that operations on a worst-case unbalanced tree with h=n (essentially a linked list) will still be `O(n)`.

<p align="center"><img src="img/tree.png"/></p>

### Balanced Trees & Other Tree Data Structures

Given the importance of tree height on their performance, it's no surprise extensive efforts are typically made to optimize the height of tree structures. Although the best-case scenario of a perfect tree (in which the descendants of each nodes are perfectly balanced) is not always achievable their are a variety of algorithms available that aim to balance trees using different criteria. **AVL trees** use a height balancing algorithm that compares the height of child sub-trees to determine whether the tree is in a state of in balance before performing a series of rotations to restore balance. 

A **binary heap** also uses the binary tree structure, and are frequently used to implement priority queues. The distinguishing feature of a min-heap is that every child contains a key less than or equal to its parent (and vice versa for max-heaps). A **B+-tree** is another example of a balanced *N*-ary tree with a variable (and typically large) number of children for each node that is particularly useful in retrieval of block-oriented storage contexts (i.e file systems). Finally, unlike an *N*-ary tree, a **multi-way (*M*-way) search tree** can store *M*-1 elements and can have up to *M* sub-trees.

> #### Project 3: [AVL Search Tree](<3 AVL Search Tree/>)
> | Complete?			| Description 	| Grade |
> | :---: 				| :--- 			| --- 	|
> | :heavy_check_mark:	| \<Type\> templated, self-balancing binary search tree w/iterator protected nodes | **16/16** (100%) |

---
## Sorting Algorithms

At a fundamental level sorting involves taking an abstract list containing unsorted objects and converting it into a list of linearly ordered objects (an Abstract Sorted Lists). These operations are typically performed on arrays since they are the data type most commonly used for storing. *In-place* sorting algorithms can perform this conversion without making a second copy of the list in memory meaning memory allocation is `Ө(1)` at most. In terms of run-time efficiency, sorting algorithms fall into three different categories: `Ө(n)`, `Ө(n·ln(n))`, and `O(n^2)`, depending on the degree of unsortedness in the list an other factors. Of course, since every sorting algorithm must inspect every one of the n elements being sorted at least once, there is a `Ω(n) ` lower bound on the run-time of sorting algorithms (`Ω(n·ln(n)` being more realistic in most scenarios). The following descriptions assume elements are being sorted in ascending order from left to right.

### O(n<sup>2</sup>) sorts
- **Insertion sort** starts from the second element in an array and compares it to the element to its left (using nested `for` loops). Under the condition that the element to its left is smaller, the current element is swapped with the lesser element until this condition is no longer true, at which point the current element is updated to the next unsorted object. As a result, after *k* iterations, the first *k* elements will be sorted. Subsequent iterations will insert an element from the unsorted section (right side) of the list into the sorted section (left side) of the list. Insertion sort is an *online* algorithm meaning it can sort a stream of inputs without knownig the final size of the list.

<p align="center"><img src="img/insert-sort.gif"/></p>

- **Bubble sort** uses the opposite strategy; the first element is swapped with the element to its right until the element to its right is greater than the current element. After *k* iterations we are only guaranteed the right-most (largest) *k* items will be ordered. Unlike iterations of insertion sort (which terminate early when the current element finds its sorted position), every iteration of bubble sort requires every element in the unsorted section of the list be compared with its neighbor. with no opportunity for early termination. This gives insertion sort the advantage when it comes to partially-sorted lists. Moreover, because bubble sort relies on assuming the right-most element is always the global maximum, it is not an online algorithm meaning the algorithm, requiring bubble sort to restart every time an item is added to the list.

<p align="center"><img src="img/bubble-sort.gif"/></p>

-  **Selection sort**, closely resembles insertion sort, but searches for the smallest unsorted element at every iteration before moving it to the (sorted) front of the array (rather than sorting the left-most unsorted element in each iteration) making it slightly less efficient than insertion sort.

### Ө(n·ln(n)) sorts
- **Quick sort**
- **Merge sort**

### Ө(n) sorts
- **Bucket sort**
- **Radix sort**

### Summary: Sorting Algorithms

| Algorithm			| Best			| Average		| Worst			| In-place? 		|
| :--- 				| :--- 			|:---			|:---			| :---: 			|
| Selection sort	| `Ω(n^2)`		|`Ө(n^2)`		|`O(n^2)`		| :heavy_check_mark:|
| Bubble sort		| `Ω(n)`		|`Ө(n^2)`		|`O(n^2)`		| :heavy_check_mark:|
| Insertion	sort	| `Ω(n)`		|`Ө(n^2)`		|`O(n^2)`		| :heavy_check_mark:|
| Heap sort			| `Ω(n·ln(n))`	|`Ө(n·ln(n))`	|`O(n·ln(n))`	| :heavy_check_mark:|
| Merge sort		| `Ω(n·ln(n))`	|`Ө(n·ln(n))`	|`O(n·ln(n))`	| :x:				|
| Quick sort		| `Ω(n·ln(n))`	|`Ө(n·ln(n))`	|`O(n^2)`		| :x:				|










