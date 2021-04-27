# AVL Tree
Implementation of an AVL Tree with nodes. Must have the following operations:
- put(key,value): insert a key/value pair into the AVL tree
- get(key): return value associated with the key
- remove(key): remove key from tree
- levelorder: prints a levelorder traversal of the tree map. key: value(balance).
- ***balance is the number of nodes on the left side of a node minus the number of nodes on the right side

Input
- First line of input will be an integer n, indicating how many commands follow.
- The next n lines will cosist of 1 of 4 commands( put, get , remove, levelorder)

Sample Input
- 13
- put 5 apple
- put 3 orange
- put 2 lime
- put 9 lemon
- levelorder
- remove 2 lime
- levelorder
- remove 9 lemon
- levelorder
- get 9
- get 5

Sample Output
- 3:orange(-1) 2:lime(0) 5:apple(-1) 9:lemon(0) 
- 5:apple(0) 3:orange(0) 9:lemon(0)
- 5:apple(1) 3:orange(0) 
- Not Found
- apple
