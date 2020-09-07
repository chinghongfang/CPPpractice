## tree.h
Make a tree by inputting string.
Print tree structure.
print\_tree(): Print all tree nodes layer by layer including "nullptr".

## avl\_tree.h
AVL\_tree is a self-balance tree. All insertion and deletion should be done by the public "insert()" function and "del()" function. These two functions keep the private data "diff" which is used to balance the tree height correct.
### How it works?
+ insertion(X): Recursively search downward the root, then insert X to the correct position. After insertion, we determine wheather to change "diff" which means "difference of right-subtree height and left-subtree height". By returning "1" or "0", let the parent node knows wheather the returning subtree increase its height. Always check for tree balance after "diff" changes.
The code can be departed into two parts. First part goes down to find the position to insert. Second part updates the factor(diff) store in the node by the return value from children nodes.
Time complexity O(lg(V)). (V is the number of nodes)
+ balance(): Choose the ways to rotate the tree. We assume that the avl\_tree add the node and delete node "one by one" and we always balance the tree when some nodes have "diff" equals 2 or -2. There are four ways to rotate the tree according to wikipedia. They are 
    - "rotate left", when diff=2 and right node>=0
    - "rotate right", when diff=-2 and left node<=0
    - "right node rotate right, this node rotate left", when diff=2 and right node diff<0
    - "left node rotate left, this node rotate right", when diff=-2 and left node diff>0
(left/right)\_rot(): While doing (left/right) rotate, the **(right/left) node must exist**.
```
     X                Z
    / \      left    / \
   t1  Z      =>    X   t3
      / \    rot   / \
     t2  t3       t1  t2

       X            Z
      / \    right / \
     Z   t3   =>  t1  X
    / \      rot     / \
   t1  t2           t2  t3
```
+ del(X): Binary search for X. Delete it and balance if needed. It is a recursive function until the value X is found because the "diff" need to be maintained. After finding the value X, we move the middle node of that subtree (subtree that root from "X value node") to cover the "X value node". Middle node is chosen by taking "left-most right subtree". After moving the middle node "X value node", we update the "diff". Always check for balance after the "diff" changes.
WARNING: If this function return "-2", it means this pointer was deleted. You will need to ```new``` a new "avl" to create a new avl-tree.
Time complexity O(lg(V)). (V is the number of nodes)
```
     t1               t1
    /  \             /  \
   X    t2          M    t2
  / \        =>    / \
 t3  t4           t3  t4
    /
   M
```

## red\_black.h
Red-black tree is also a self-balance tree. In c++ standard template library in set.h, std::set is an implementation of red-black tree. Please include <set> and use the class "set" when there is in need of red-black tree data structure. There are more functions in <set> than mine "red_black.h". I just write for fun. This structure uses contains only two pointer variables, template value and one byte "color" for each node. I do my best on reducing the memory cost on this structure.
### How it works?
Definition of red-black tree:
1. All nodes are either red or black.
2. Root is black.
3. All children of red node is black.
4. All leaves(nullptr) is black.
5. Assume $T$ is a red-black tree
    $\forall n \in T$, $n$ is a node of $T$
    for all path $P$ from $n$ to leaves,
    number of black nodes on $P$ is constant
+ insert(X): It can be departed into two parts. First is recursive down from root to leaf node. Second is getting returned value of children and returning another value to parent.
There are three kinds of returned value. "0" means no need to do anything, this is a red-black tree now. "1" means one of its child turned red due to repaint. Need to return to parent and do balance if needed. "2" or "-2" means one of grandchild is inserted or turned red. Determine which balance method to do or no need to balance.
