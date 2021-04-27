# AVL Tree
Implementation of an AVL Tree with nodes. Must have the following operations:
- put(key,value) 
- get(key)
- remove(key)
- levelorder

Input
- First line of input will be an integer n, indicating how many commands follow.
- The next n lines will cosist of 1 of 4 commands( put, get , remove, levelorder)

Sample Input
- 11
- put 5 apple
- put 3 orange
- put 2 lime
- put 9 lemon
- levelorder
- remove 2 lime
- levelorder
- remove 9 lemon
- levelorder

Sample Output
- 3:orange(-1) 2:lime(0) 5:apple(-1) 9:lemon(0) 
- 5:apple(0) 3:orange(0) 9:lemon(0)
- 5:apple(1) 3:orange(0) 
