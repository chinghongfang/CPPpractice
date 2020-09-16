#ifndef AVL_TREE
#define AVL_TREE
#include<stack>

// Please use new operator to create "class avl".
// Because the "del()" function may "delete" the node you create.
template<class T>
class avl{
    public:
        avl(){
            diff = 5;
            left = nullptr;
            right = nullptr;
        }
        ~avl(){
            if (this->left) delete this->left;
            if (this->right) delete this->right;
        }

        int insert(T val);      // O(lg(n)), n is number of elements in the tree
        // if return value of del() == -2, last node has been deleted
        int del(T val);         // O(lg(n)), n is number of elements in the tree
        T val;
        avl<T>* left;
        avl<T>* right;
    //private:
        char balance();
        void left_rot();
        void right_rot();
        int del_this();
        char diff;
};
// assume the tree "this" is a avl tree already
// class T needs "operator <"
// class T needs "operator ="
// class T needs "operator =="
// (Duplicate val will not be inserted.)
template<class T>
int avl<T>::insert(T val){
    int factor;
    if (this->diff == 5) {
        this->val = val;
        this->diff = 0;
        return 0;
    }
    if (val < this->val && this->left){             // class T operator <
        factor = - ( this->left->insert(val) );
    }else if (val == this->val){ return 0;          // make all val unique in tree
    }else if (this->val < val && this->right){
        factor = this->right->insert(val);
    }else {
        // here is leaf node. Determine which side to add new node
        if (val < this->val){
            // add the new node to left
            this->left = new avl<T>;
            this->left->val = val;
            this->left->diff = 0;

            // update the height factor -- "diff"
            factor = -1;
        }else {
            // add the new node to right
            this->right = new avl<T>;
            this->right->val = val;             // class T operator =
            this->right->diff = 0;

            // update the height factor
            factor = 1;
        }
    }

    if (factor == 0) return 0;
    this->diff += factor;
    char ret = 0;
    if (factor < 0){
        if (this->diff < 0) ret = 1;
        if (this->diff == -2){
            ret += this->balance();
        }
    }else {
        if (this->diff > 0) ret = 1;
        if (this->diff == 2){
            ret += this->balance();
        }
    }
    return ret;
}
template<class T>
char avl<T>::balance(){
    // check
    if (this->diff != 2 && this->diff != -2) return 0;

    char ret = -1;
    if (this->diff > 0){        // diff == 2  (right heavy)
        if (this->right->diff == 0) ret = 0;        // only one situation not change tree height
        if (this->right->diff < 0)
            this->right->right_rot();
        this->left_rot();
    }else {                     // diff == -2 (left heavy)
        if (this->left->diff == 0) ret = 0;         // only one situation not change tree height
        if (this->left->diff > 0)
            this->left->left_rot();
        this->right_rot();
    }
    return ret;
}
//     X             Z
//    / \           / \
//   t1  Z    =>   X   t3
//      / \       / \
//     t2 t3     t1  t2
template<class T>
void avl<T>::left_rot(){
    avl<T>* Z = this->right;
    // height compare to t1
    char t2_h = this->diff - 1 - ((this->right->diff)<0?0:this->right->diff);
    char t3_h = this->diff - 1 + ((this->right->diff)>0?0:this->right->diff);

    this->right = Z->right;
    Z->right = Z->left;
    Z->left = this->left;
    this->left = Z;

    this->diff = t3_h - 1 - (t2_h>0?t2_h:0);
    this->left->diff = t2_h;

    T tmp = this->val;
    this->val = Z->val;
    Z->val = tmp;

    return;
}
//      X             Z
//     / \           / \
//    Z   t3   =>   t1  X
//   / \               / \
//  t1  t2            t2  t3
template<class T>
void avl<T>::right_rot(){
    avl<T>* Z = this->left;
    // height compare to t3
    char t1_h = -(this->diff) - 1 - ((this->left->diff)<0?0:this->left->diff);
    char t2_h = -(this->diff) - 1 + ((this->left->diff)>0?0:this->left->diff);
    this->left = Z->left;
    Z->left = Z->right;
    Z->right = this->right;
    this->right = Z;

    this->diff = -(t1_h - 1 - (t2_h>0?t2_h:0));
    this->right->diff = -t2_h;

    T tmp = this->val;
    this->val = Z->val;
    Z->val = tmp;

    return;
}

template<class T>
int avl<T>::del(T val){
    int factor;
    if (val == this->val){
        factor = this->del_this();
        // factor == -2 ==> this pointer is deleted, return to parent node and set null
        return factor;

    }else if (val < this->val && this->left) {
        factor = - ( this->left->del(val) );
    }else if (!(val < this->val) && this->right){
        factor = this->right->del(val);
    }else factor = 0;           // val not exists


    if (factor == 2){           // left is empty now
        delete this->left;
        this->left = nullptr;
        this->diff += 1;
        // tree balance 
        if (this->diff == 2) {
            return (int)(this->balance());
        }

        if (this->diff <= 0) return -1;
    }else if (factor == -2){    // right is empty now
        delete this->right;
        this->right = nullptr;
        this->diff -= 1;
        // tree balance
        if (this->diff == -2){
            return (int)(this->balance());
        }

        if (this->diff >= 0) return -1;

    }else if (factor != 0){     // left or right subtree height decrease
        this->diff += factor;
        if (this->diff >= 0 && factor < 0){
            return -1;
        }else if (this->diff <= 0 && factor > 0){
            return -1;
        }else if (this->diff == 2 || this->diff == -2){         // tree balance
            return (int)(this->balance());
        }
    }
    return 0;
}
// Remove the root node and put the middle node to the root.
// The middle node is chosen by "left most" leaf of the "right subtree"
template<class T>
// return value: 0 no height change, -1 height decrease, -2 this node deleted
int avl<T>::del_this(){
    avl<T>* mid;
    std::stack<avl<T>*> stk;
    if (this->right) {
        mid = this->right;
        while (mid->left) {
            stk.push(mid);
            mid = mid->left;
        }
        // left most get!

        this->val = mid->val;           // middle node goes to the deleted node
        if (!stk.empty()){
            stk.top()->left = mid->right;   // deal with the go away node
            mid->right = nullptr;
            delete mid;

            int tmp = -1;
            while (!stk.empty()){
                if (tmp < 0){
                    tmp = stk.top()->diff;
                    stk.top()->diff += 1;           // left subtree decrease
                    if (stk.top()->diff == 2){
                        // do balancing and check height
                        if (stk.top()->balance()){  // if return -1, keep update parents' diff
                            tmp = -1;
                        }
                    }
                }else {
                    tmp = 0;
                    break;
                }
                stk.pop();
            }
            if (tmp < 0){                   // causing height of right subtree decrease
                this->diff -= 1;
                if (this->diff >= 0) return -1; // this tree height decrease
                if (this->diff == -2) return this->balance();
            }
        }else {                         // the head of right subtree is the left most node
            this->right = mid->right;
            mid->right = nullptr;
            delete mid;
            this->diff -= 1;
            if (this->diff >= 0) return -1;     // this tree height decrease
            if (this->diff == -2) return this->balance();
        }

    }else if (this->left){      // right subtree empty, left exists
        // there is no right subtree, so we just make the left subtree be the new tree
        mid = this->left;       // just a tmp value
        this->left = mid->left;
        this->right = mid->right;
        this->val = mid->val;
        this->diff = mid->diff;

        mid->left = nullptr;
        mid->right = nullptr;
        delete mid;
        return -1;
    }else {
        return -2;
    }
    return 0;
}
#endif
