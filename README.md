## [ECE 250 - Data Structures & Algorithms](https://ece.uwaterloo.ca/~dwharder/aads/Outline/)
**Course Objectives**

> Introduce the student to the concept of data structures through abstract data structures including lists, sorted lists, stacks, queues, deques, sets/maps, directed acyclic graphs, and graphs; and implementations including the use of linked lists, arrays, binary search trees, M-way search trees, hash tables, complete trees, and adjacency matrices and lists.

> Introduce the student to algorithms design including greedy, divide-and-conquer, random and backtracking algorithms and dynamic programming; and specific algorithms including, for example, resizing arrays, balancing search trees, shortest path, and spanning trees.

---
## Background

Data strucutres & algorithms govern the way we interact with digital information. At the highest level, they are used to organize and access abstract data types like containers (which store collections of objects).

### Relationships & Orderings
The relationship between objects is often just as important as the information stored in the object. Most data structures can be described using the following six relationships:

- **Linear orderings** - Every object is strictly less than, equal to, or greater than another and vice versa (transative)
  - *Examples*: Integer & Real Number sets, hexadecimal memory addresses, the alphabet
- **Hierarchical orderings** - Each object has a *parent* object with the exception of a singular *root* object
  - *Examples*: Unix directories, class inheritance in C# and Java
- **Partial orderings** - A hierarchical ordering with 1 or more root and no loops
  - *Examples*: C++ classes (multiple inheritance), compilation dependencies
- **Equivalence relations** - Relationships where objects can be partitioned into subsets (equivalence relations) with owhter 'weakly' related (x~y) objects
  - *Examples*: Landau symbol *Ө* ```2n ~ 5n ∈ Ө(n)```
- **Weak orderings** - A linear ordering of equivalence classes
  - *Examples*: Big-O notation ```O(1) < O(ln(n)) < O(n•ln(n))``` 
- **Adjacency Relations** - Relationships described by one object being connected to another (x ↔ y)
  - *Examples*: Graphs, social networks
  
### Asymptotic Analysis & Big-O Notation
It's often useful to analyze and compare algorithms with respect to one or more variables (i.e. run-time, memory). Using the same 'Big O' mathematical notation and Landau symbols used to describe the limiting behaviour of a function, the efficiency of different algorithms can be compared. For two algorithms described by the functions ```f(n)``` and ```g(n)```, the best- and worst-case behaviour of the algorithms  can be described as such (*n* can be a measure of run-time or memory):
- ```f(n) = o(g(n))``` when ```f(n)``` approaches ∞ at a slower rate than ```g(n)``` (**f outperforms g**)
- ```f(n) = O(g(n))``` when ```f(n)``` approaches ∞ at a rate equal to or slower than ```g(n)``` (**f, at *worst*, performs the same g**)
- ```f(n) = Ω(g(n))``` when ```f(n)``` approaches ∞ at a rate faster than or equal to ```g(n)``` (**f, at *best*, performs the same g**)
- ```f(n) = ω(g(n))``` when ```f(n)``` approaches ∞ at a much slower rate than ```g(n)``` (**g outperforms f**)
- ```f(n) = Ө(g(n))``` when ```f(n)``` and ```g(n)``` approach ∞ at comparable rates (**f and g perform roughly the same**)

Note that since this notation descibes limiting behaviour, one should be wary of making objective statements about the relative performance of two different algorithms without context. As a result, even though f may run faster than g on 1 million objects, the opposite could be true when the same algorithms are run on only 1000 objects. Similarly, since Big-O notation gives information about the relative scaling of different algorithms rather than their absolute performance, for an algorithm f that is faster than another, g, by a constant factor, ```f(n) = Ө(g(n))``` is still true.

---
## Linked Lists

Linked lists are the simplest type of data structure, consisting of a set of linearly ordered nodes that, in addition to storing data, also contain an adress pointing to the location next node in memory.

- Pros: Simple, O(1) insertions w/out reallocation
- Cons: Inefficient Indexing, poor cache locality

### Project 1: [Doubly Linked Sentinel List](https://ece.uwaterloo.ca/~dwharder/aads/Projects/1/Double_sentinel_list/) (24/24)
\<Type\> templated linked list w/a second sentinel at the end (for improved indexing/insertion at the back of the list) and O(1) copy & move contructors.
  
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
