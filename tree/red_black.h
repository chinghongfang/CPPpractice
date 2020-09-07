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
template<class T>
class rb{
    public:
        T val;
        rb(){
            color = -1;
            left = nullptr;
            right = nullptr;
        }
        char insert(T);
        rb* left;
        rb* right;
    private:
        void insert_balance();
        void left_rot();
        void right_rot();
        char color;
};
// Ignore the return value. It is for recursive use.
template<class T>
char rb<T>::insert(T val){
    char factor;
    bool go_left;
    // First part, recursively find the place to insert
    if (color == -1){
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
    }else if (val < this->val){
        this->left = new rb;
        this->left->color = 1;
        this->left->val = val;
        if (this->color == 0) return 0; // parent is black, no need to change.
        return -2;                      // return to grandparent and then balance.
    }else {
        this->right = new rb;
        this->right->color = 1;
        this->right->val = val;
        if (this->color == 0) return 0;
        return 2;                       // return to grandparent and then balance.
    }


    // Second part, do something determined by returned value from children
    // no need do balance on this node
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
    // parent and uncle are both red
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
    // recover the node which should be red painted black.
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
    this->val = Z->val;
    Z->val = tmp;
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
    this->val = Z->val;
    Z->val = tmp;
    return;
}
#endif
