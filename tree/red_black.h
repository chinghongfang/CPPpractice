// std::set is a red-black tree implementation.
// You can just include <set> to use more and more powerful function.
// This code is just for practice!!

// Rules for red-black tree.
// 1. All nodes are either red(1) or black(0).
// 2. Root node is always black(0).
// 3. All children of red(1) node are black(0).
// 4. For all node N, 
//      For all path from N to any leaf,
//          the number of black nodes on the path are the same
#ifndef RED_BLACK
#define RED_BLACK
#include<cassert>
using namespace std;
template<class T>
class rb{
    public:
        T val;
        rb(){
            color = -1;
            left = nullptr;
            right = nullptr;
        }
        ~rb(){
            if (this->left) delete this->left;
            if (this->right) delete this->right;
        }
        char insert(T);
        char del(T);
        rb* left;
        rb* right;
    private:
        void insert_balance();
        void left_rot();
        void right_rot();
        char del_this();
        char find_most();
        char balance(bool);
        char color;
};
// Ignore the return value. It is for recursive use.
template<class T>
char rb<T>::insert(T val){
    char factor;
    bool go_left;
    // First part, recursively find the place to insert
    if (color == -1){       // root node, no need to "new" a new node
        this->val = val;
        color = 0;
        return 0;
    }
    if (val == this->val){
        return 0;           // duplicate value, ignore this insert value
    }else if (val < this->val && this->left){
        factor = this->left->insert(val);
        go_left = true;
    }else if (this->val < val && this->right){
        factor = this->right->insert(val);
        go_left = false;

    // insertion position found
    }else if (val < this->val){     // insert to left child
        this->left = new rb<T>;
        this->left->color = 1;
        this->left->val = val;
        if (this->color == 0) return 0; // parent is black, no need to change.
        return -2;                      // return to grandparent and then balance.
    }else {                         // insert to right child
        this->right = new rb<T>;
        this->right->color = 1;
        this->right->val = val;
        if (this->color == 0) return 0; // parent is black, no need to balance.
        return 2;                       // return to grandparent and then balance.
    }


    // Second part, do something determined by returned value from children
    // no need of balance, keep returning
    if (factor == 0) return 0;
    // parent node goes to grandparent
    if (factor == 1) {
        // recover the red node
        if (go_left) this->left->color = 1;
        else this->right->color = 1;
        // repair grandparent or not
        if (this->color){           // need to repair grandparent
            if (go_left) return -2;
            else return 2;
        }
        return 0;
    }
    // grandparent node balance
    if (this->left && this->left->color && this->right && this->right->color){
        // Parent and uncle are both red.
        // Then paint grandparent(this) red(1), and paint parent and uncle black.
        // Because grandparent(this) is red(1), repair grandparent(this).
        //this->color = 1;
        this->color = 0;            // it should be red, but we don't know if it is red
        this->left->color = 0;
        this->right->color = 0;
        return 1;                   // repair grandparent node
    }else if (go_left){                             // parent red, uncle black, right children red
        if (factor > 0) this->left->left_rot();    // change to outer children
        this->right_rot();
        this->color = 0;
        this->right->color = 1;
    }else {
        if (factor < 0) this->right->right_rot(); // change to outer children
        this->left_rot();
        this->color = 0;
        this->left->color = 1;
    }
    return 0;
}
//    X             Z
//   / \           / \
//  t1  Z    =>   X   t3
//     / \       / \
//    t2  t3    t1  t2
//  Copy all Z's data to X node, so no need to change parent node.
template<class T>
void rb<T>::left_rot(){
    rb<T>* Z = this->right;

    this->right = Z->right;
    Z->right = Z->left;
    Z->left = this->left;
    this->left = Z;

    T tmp = this->val;
    char tmp_c = this->color;
    this->val = Z->val;
    this->color = Z->color;
    Z->val = tmp;
    Z->color = tmp_c;
    return;
}
//      X         Z
//     / \       / \
//    Z   t3 => t1  X
//   / \           / \
//  t1  t2        t2  t3
template<class T>
void rb<T>::right_rot(){
    rb<T>*Z = this->left;

    this->left = Z->left;
    Z->left = Z->right;
    Z->right = this->right;
    this->right = Z;

    T tmp = this->val;
    char tmp_c = this->color;
    this->val = Z->val;
    this->color = Z->color;
    Z->val = tmp;
    Z->color = tmp_c;
    return;
}

template<class T>
char rb<T>::del(T val){
    if (this->color == -1) return 0;        // empty tree now
    char factor;
    bool right;
    if (val < this->val){
        if (this->left) factor = this->left->del(val);
        else return 0;
        right = false;
    }else if (this->val < val){
        if (this->right) factor = this->right->del(val);
        else return 0;
        right = true;
    }else{
        // find it!!
        return this->del_this();
    }

    // deal with return value
    if (factor == 0) return 0;
    else if (factor == 1){      // need to delete node
        if (right){
            rb<T>* tmp = this->right;
            factor = 0;
            this->right = nullptr;
            if (tmp->color == 0) factor = this->balance(true);
            delete tmp;
        }else {
            rb<T>* tmp = this->left;
            factor = 0;
            this->left = nullptr;
            if (tmp->color == 0) factor = this->balance(false);
            delete tmp;
        }
        return factor;
    }else if (factor == -1){    // one subtree has less black node
        return this->balance(right);
    }
    // this can not happen!
    return - - - - - 1;
}
template<class T>
char rb<T>::del_this(){
    if (this->right){       // goes down to left-most right subtree
        rb<T>* now = this->right;
        while (now->left){
            now = now->left;
        }
        // left most get!!
        char factor;
        this->val = now->val;
        factor = this->right->find_most();      // find left-most
        if (factor == 1){                       // this->right is the left-most node
            rb<T>* deleted = this->right;
            this->right = deleted->right;
            factor = 0;

            if (deleted->color) ;                               // deleted red
            else if (deleted->right && deleted->right->color)   // child red
                deleted->right->color = 0;
            else factor = this->balance(true);      // right subtree has less black node

            deleted->left = nullptr;
            deleted->right = nullptr;
            delete deleted;
            return factor;
        }else if (factor == -1){
            return this->balance(true);             // (right) subtree has less black node
        }
        return 0;
    }else if (this->left){                      // "delete" this node
        // move left subtree to the deleted place
        rb<T>* child = this->left;
        char ans;
        this->right = child->right;
        this->left = child->left;
        this->val = child->val;
        if (this->color || child->color){           // either this node or child node is red
            // let this position black, then there is no red node on this,deleted nodes
            this->color = 0;
            ans = 0;
        }else if (child->left && child->right &&    // grandchildren both red
                child->left->color && child->right->color){
            child->left->color = 0;
            child->right->color = 0;
            ans = 0;
        }else {                                     // Oh no! Worst case. this subtree -1 black nodes
            // Return to parent to repair.
            ans = -1;
        }
        child->left = nullptr;
        child->right = nullptr;
        delete child;
        return ans;
    }
    // no children...
    // let the parent delete this
    return 1;
}
// Balance for one subtree which has less black node path.
// child node should be black because of the algorithm
template<class T>
char rb<T>::balance(bool right){
    rb<T>* child;
    rb<T>* sibling;
    rb<T>* inner;
    rb<T>* outer;
    if (right){
        assert(this->left && "sibling error");
        child = this->right;
        sibling = this->left;
        inner = sibling->right;
        outer = sibling->left;
    }else {
        assert(this->right && "sibling error");
        child = this->left;
        sibling = this->right;
        inner = sibling->left;
        outer = sibling->right;
    }

    // 4 cases.
    // sibling should exist. Because sibling has more black node.
    // There must exist sibling(this->right)
    // Note: left subtree of this decrease one black node.
    if (sibling->color){                // sibling red
        assert(inner && outer && "sibling child error");
        if (!right) this->left_rot();
        else this->right_rot();
        this->color = 0;
        // !! The sibling is now parent of the child
        sibling->color = 1;
        // OH NO! Worst case. Sibling need to repair first
        return sibling->balance(right);
    }else if ((inner && inner->color) || (outer && outer->color)){
        // sibling black, one of sibling's children red
        //     0/1                0/1           0/1
        //      P                  S             S1
        //     / \               /   \          /  \
        //    0   0             0     0        0    0
        //    C   S     =>      P     S2  or   P    S
        //       / \           / \            / \   / \
        //      ?   0/1       0   S1          0  t1 t2 0
        //      S1  S2        C               C        S2
        //     / \           (if S2 red)     (if S2 is black)
        //    t1  t2
        // that is we can't repaint parent black, sibling red to balance it.
        // If sibling's inner child is red, rotate sibling to make red node outer.
        if (!outer || outer->color == 0){
            if (!right) {
                sibling->right_rot();
            }else {
                sibling->left_rot();
            }
            outer = inner;
        }
        // Now it is sure that siblings's outer child is red.
        if (!right) this->left_rot();
        else this->right_rot();
        this->color = sibling->color;
        sibling->color = 0;
        outer->color = 0;
        return 0;
    }else {                                 // sibling black, sibling children black
        if (this->color == 1){
            // parent red
            // Simply repaint parent black, sibling red
            // to gain one more black node for (right/left) subtree
            this->color = 0;
            sibling->color = 1;
            return 0;
        }else {
            // parent black, sibling black, sibling's children black
            // Oh no! It is the second worst case. Need to repair by parent.
            // -1 sibling subtree black node.
            sibling->color = 1;
            return -1;
        }
    }
}
// find left-most node
// delete it and balance it
template<class T>
char rb<T>::find_most(){
    char factor;

    if (this->left){
        factor = this->left->find_most();
    }else {
        return 1;
    }

    if (factor == 0) return 0;
    // "this" is parent of (deleted node/less black node subtree root)
    else if (factor == 1){
        // delete the node
        rb<T>* tmp = this->left;
        this->left = tmp->right;
        if (tmp->color == 1){                       // delete red node
            // just delete the red node and reconnect red node child to red node parent
            tmp->left = nullptr;
            tmp->right = nullptr;
            delete tmp;
        }else if (tmp->right && tmp->right->color){  // delete black, (the only)child red
            // child repaint black
            this->left->color = 0;
            tmp->left = nullptr;
            tmp->right = nullptr;
            delete tmp;
        }else {                                     // delete black, (the only)child black
            tmp->left = nullptr;
            tmp->right = nullptr;
            delete tmp;
            return this->balance(false);
        }
    }else{              // factor == -1
        return this->balance(false);
    }
    return 0;
}
#endif
