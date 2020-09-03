##tree.h
Make a tree by inputting string.
Print tree structure.
print\_tree(): Print all tree nodes layer by layer including "nullptr".

##avl\_tree.h
AVL\_tree is a self-balance tree. All insertion and deletion should be done by the public "insert()" function and "del()" function. These two functions keep the private data "diff" which is used to balance the tree height correct.
###How it works?
+ insertion(X): Recursively search downward the root, then insert X to the correct position. After insertion, we determine wheather to change "diff" which means "difference of right-subtree height and left-subtree height". By returning "1" or "0", let the parent node knows wheather the returning subtree increase its height. Always check for tree balance after "diff" changes.
+ balance(): Choose the ways to rotate the tree. We assume that the avl\_tree add the node and delete node "one by one" and we always balance the tree when some nodes have "diff" equals 2 or -2. There are four ways to rotate the tree according to wikipedia. They are 
    - "rotate left", when diff=2 and right node>=0
    - "rotate right", when diff=-2 and left node<=0
    - "right node rotate right, this node rotate left", when diff=2 and right node diff<0
    - "left node rotate left, this node rotate right", when diff=-2 and left node diff>0
(left/right)\_rot(): While doing (left/right) rotate, the **(right/left) node must exist**.
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
+ del(X): Binary search for X. Delete it and balance if needed. It is a recursive function until the value X is found because the "diff" need to be maintained. After finding the value X, we move the middle node of that subtree (subtree that root from "X value node") to cover the "X value node". Middle node is chosen by taking "left-most right subtree". After moving the middle node "X value node", we update the "diff". Always check for balance after the "diff" changes.
WARNING: If this function return "-2", it means this pointer was deleted. You will need to ```new``` a new "avl" to create a new avl-tree.
     t1               t1
    /  \             /  \
   X    t2          M    t2
  / \        =>    / \
 t3  t4           t3  t4
    /
   M
