## Project 3: [AVL Search Tree](<3 AVL Search Tree/>)

| Complete?			| Description 	| Grade |
| :---: 				| :--- 			| --- 	|
| :heavy_check_mark:	| <Type> templated, self-balancing binary search tree w/iterator protected nodes | **16/16** (100%) |
**Full Description:** https://ece.uwaterloo.ca/~dwharder/aads/Projects/3/AVL_tree/
   
##### Function Signatures
- Search_tree();
- ~Search_tree();

- bool empty() const;
- int size() const;
- int height() const;

- Type front() const;
- Type back() const;

- Iterator begin();
- Iterator end();
- Iterator rbegin();
- Iterator rend();
- Iterator find( Type const & );

- void clear();
- bool insert( Type const & );
- bool erase( Type const & ); 