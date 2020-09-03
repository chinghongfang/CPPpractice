#ifndef AVL_TREE
#define AVL_TREE
#include<stack>

// Please use new operator to create "class avl".
// Because the "del()" function may "delete" the node you create.
template<class T>
class avl{
    public:
        avl(){
            diff = 0;
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
    private:
        void balance();
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
    if (val < this->val && this->left){             // class T operator <
        factor = - ( this->left->insert(val) );
    }else if (val == this->val){ return 0;          // make all val unique in tree
    }else if (!(val < this->val) && this->right){
        factor = this->right->insert(val);
    }else {
        // here is leaf node. Determine which side to add new node
        if (val < this->val){
            // add the new node to left
            this->left = new avl<T>;
            this->left->val = val;

            // update the height factor -- "diff"
            factor = -1;
        }else {
            // add the new node to right
            this->right = new avl<T>;
            this->right->val = val;             // class T operator =

            // update the height factor
            factor = 1;
        }
    }

    if (this->diff == 0){
        this->diff += factor;
        return 1;
    }else {
        this->diff += factor;
        //  do balance when |this->diff| == 2)
        if (this->diff == 2 || this->diff == -2){
            this->balance();
        }
        return 0;
    }
}
template<class T>
void avl<T>::balance(){
    // check
    if (this->diff != 2 && this->diff != -2) return;

    if (this->diff > 0){        // diff == 2  (right heavy)
        if (this->right->diff < 0){
            this->right->right_rot();
            this->left_rot();
        }else {
            this->left_rot();
        }
    }else {                     // diff == -2 (left heavy)
        if (this->left->diff > 0){
            this->left->left_rot();
            this->right_rot();
        }else {
            this->right_rot();
        }
    }
    return;
}
//     X             Z
//    / \           / \
//   t1  Z    =>   X   t3
//      / \       / \
//     t2 t3     t1  t2
template<class T>
void avl<T>::left_rot(){
    avl<T>* t1 = this->left;
    avl<T>* t2 = this->right->left;
    avl<T>* t3 = this->right->right;
    // height compare to t1
    char t2_h = this->diff - 1 - ((this->right->diff)<0?0:this->right->diff);
    char t3_h = this->diff - 1 + ((this->right->diff)>0?0:this->right->diff);

    this->left = this->right;
    this->right = t3;

    this->left->left = t1;
    this->left->right = t2;

    this->diff = t3_h - 1 - (t2_h>0?t2_h:0);
    this->left->diff = t2_h;

    T tmp = this->val;
    this->val = this->left->val;
    this->left->val = tmp;

    return;
}
//      X             Z
//     / \           / \
//    Z   t3   =>   t1  X
//   / \               / \
//  t1  t2            t2  t3
template<class T>
void avl<T>::right_rot(){
    avl<T>* t1 = this->left->left;
    avl<T>* t2 = this->left->right;
    avl<T>* t3 = this->right;
    // height compare to t3
    char t1_h = -(this->diff) - 1 - ((this->left->diff)<0?0:this->left->diff);
    char t2_h = -(this->diff) - 1 + ((this->left->diff)>0?0:this->left->diff);
    this->right = this->left;
    this->left = t1;

    this->right->left = t2;
    this->right->right = t3;

    this->diff = -(t1_h - 1 - (t2_h>0?t2_h:0));
    this->right->diff = -t2_h;

    T tmp = this->val;
    this->val = this->right->val;
    this->right->val = tmp;

    return;
}
// need "operator ==" in class T
template<class T>
int avl<T>::del(T val){
    int factor;
    if (val == this->val){
        factor = this->del_this();
        if (factor == -2) return -2;    // this pointer is deleted, return to parent node and set null
        return factor;

    }else if (val < this->val && this->left) {
        factor = - ( this->left->del(val) );
    }else if (!(val < this->val) && this->right){
        factor = this->right->del(val);
    }else factor = 0;           // val not exists


    if (factor == 2){           // left is empty now
        this->left = nullptr;
        this->diff += 1;
        // tree balance 
        if (this->diff == 2) {
            if (this->right->diff == 0){    // one deletion situation will not change tree height
                this->balance();
                return 0;
            }
            this->balance();
            return -1;
        }

        if (this->diff <= 0) return -1;
    }else if (factor == -2){    // right is empty now
        this->right = nullptr;
        this->diff -= 1;
        // tree balance
        if (this->diff == -2){
            if (this->left->diff == 0){     // one deletion situation will not change tree height
                this->balance();
                return 0;
            }
            this->balance();
            return -1;
        }

        if (this->diff >= 0) return -1;

    }else if (factor != 0){     // left or right subtree height decrease
        this->diff += factor;
        if (this->diff >= 0 && factor < 0){
            return -1;
        }else if (this->diff <= 0 && factor > 0){
            return -1;
        }else if (this->diff == 2){         // tree balance
            if (this->right->diff == 0){
                this->balance();
                return 0;
            }
            this->balance();
            return -1;
        }else if (this->diff == -2){        // tree balance
            if (this->left->diff == 0){
                this->balance();
                return 0;
            }
            this->balance();
            return -1;
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

        this->val = mid->val;           // middle node goes to the deleted node
        if (!stk.empty()){
            stk.top()->left = mid->right;   // deal with the go away node
            mid->right = nullptr;
            delete mid;

            int tmp = -1;
            while (!stk.empty()){
                if (tmp < 0){
                    tmp = stk.top()->diff;
                    stk.top()->diff += 1;
                }else {
                    tmp = 0;
                    break;
                }
                stk.pop();
            }
            if (tmp < 0){                   // causing height of right subtree decrease
                this->diff -= 1;
                if (this->diff >= 0) return -1; // this tree height decrease
            }
        }else {                         // the head of right subtree is the left most node
            this->right = mid->right;
            mid->right = nullptr;
            delete mid;
            this->diff -= 1;
            if (this->diff >= 0) return -1;     // this tree height decrease
        }
    }else if (this->left){
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
        delete this;
        return -2;
    }
    return 0;
}
#endif
