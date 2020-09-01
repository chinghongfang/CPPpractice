#ifndef AVL_TREE
#define AVL_TREE

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

        int insert(T val);
        T val;
        avl<T>* left;
        avl<T>* right;
    private:
        void balance();
        void left_rot();
        void right_rot();
        char diff;
};

// assume the tree "this" is a avl tree already
// class T needs "operator <"
// class T needs "operator ="
template<class T>
int avl<T>::insert(T val){
    int factor;
    if (val < this->val && this->left){         // class T operator <
        factor = - ( this->left->insert(val) );
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
#endif
