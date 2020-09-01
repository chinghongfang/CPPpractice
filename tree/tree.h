/*
 Binary tree structure, function to construct binary tree 
 and function to print the tree.
*/
#ifndef TREE
#define TREE
#include<queue>
#include<iostream>
#include<string>
template <class T>
class node{
    public:
        node(){
            left = nullptr;
            right = nullptr;
        }
        ~node(){
            if (this->left) delete this->left;
            if (this->right) delete this->right;
        }
        T val;
        node* left;
        node* right;
};
node<int>* str_to_tree(char* str);
node<int>* str_to_tree(std::string str);
template<class T> void print_tree(T* root);

// string to integer tree
// example format: "[1, null, 2,3,4]"
//        1
//         \
//          2
//         / \
//        3   4
// Please delete the returned node after use
// example:
//      '''
//      node<int>* root = str_to_tree("[1,null,2,3,4]");
//      //...
//      delete root;
//      '''
node<int>* str_to_tree(char* str){
    node<int>* head = new node<int>;
    int i = 0;
    int tmp_val = 0;
    bool neg = false;
    int fill = -3;
    char nul = '\0';

    std::queue<node<int>*> que;
    que.push(head);
    while (str[i] != '\0' && !que.empty()){
        // parse numbers
        if (str[i] == '-'){
            neg = !neg;
        }else if (str[i]>='0' && str[i]<='9'){
            tmp_val *= 10;
            tmp_val += str[i]-'0';
            if (fill < 0) fill += 3;
        // parse null
        }else if (str[i] == 'n'){
            nul = 'n';
        }else if (str[i] == 'u'){
            if (nul == 'n') nul = 'u';
            else nul = '\0';
        }else if (str[i] == 'l'){
            if (nul == 'u') nul = 'l';
            else if (nul == 'l'){
                if (fill == -2){
                    que.front()->left = nullptr;
                    fill = -1;
                }else if (fill == -1){
                    que.front()->right = nullptr;
                    que.pop();
                    fill = -2;
                }
                nul = '\0';
            }else nul = '\0';
        // check to fill in
        }else if (fill >= 0){
            if (neg) tmp_val = -tmp_val;
            if (fill == 0){
                que.front()->val = tmp_val;
                fill = -2;
            }else if (fill == 1){
                que.front()->left = new node<int>;
                que.front()->left->val = tmp_val;
                que.push(que.front()->left);
                fill = -1;
            }else if (fill == 2){
                que.front()->right = new node<int>;
                que.front()->right->val = tmp_val;
                que.push(que.front()->right);
                fill = -2;
                que.pop();
            }
            neg = false;
            tmp_val = 0;
        }
        ++i;
    }
    return head;
}
node<int>* str_to_tree(std::string str){
    node<int>* head = new node<int>;
    int i = 0;
    int tmp_val = 0;
    bool neg = false;
    int fill = -3;
    char nul = '\0';

    std::queue<node<int>*> que;
    que.push(head);
    for (int i = 0; i<str.size() && !que.empty(); ++i){
        // parse numbers
        if (str[i] == '-'){
            neg = !neg;
        }else if (str[i]>='0' && str[i]<='9'){
            tmp_val *= 10;
            tmp_val += str[i]-'0';
            if (fill<0) fill += 3;
        // parse null
        }else if (str[i] == 'n'){
            nul = 'n';
        }else if (str[i] == 'u'){
            if (nul == 'n') nul = 'u';
            else nul = '\0';
        }else if (str[i] == 'l'){
            if (nul == 'u') nul = 'l';
            else if (nul == 'l'){
                if (fill == -2){
                    que.front()->left = nullptr;
                    fill = -1;
                }else if (fill == -1){
                    que.front()->right = nullptr;
                    que.pop();
                    fill = -2;
                }
                nul = '\0';
            }else nul = '\0';
        // check to fill in
        }else if (fill >= 0){
            if (neg) tmp_val = -tmp_val;
            if (fill == 0){
                que.front()->val = tmp_val;
                fill = -2;
            }else if (fill == 1){
                que.front()->left = new node<int>;
                que.front()->left->val = tmp_val;
                que.push(que.front()->left);
                fill = -1;
            }else if (fill == 2){
                que.front()->right = new node<int>;
                que.front()->right->val = tmp_val;
                que.push(que.front()->right);
                fill = -2;
                que.pop();
            }
            neg = false;
            tmp_val = 0;
        }
    }
    return head;
}

// Please overload your function to cout<<
// (If your node<> is standard type, then no need to overload it.)
// example:
// std::ostream& operator<<(std::ostream& os, T t){
//      os<< '(' << t.val1 << ',' << t.val2 << ')';
//      return os;
// }
template<class T>
void print_tree(T* root){
    if (!root) return;
    std::queue<T*> que;
    que.push(root);
    while (!que.empty()){
        if (que.front()){
            std::cout<<que.front()->val<<' ';
            que.push(que.front()->left);
            que.push(que.front()->right);
        }else {
            std::cout<<"null"<<' ';
        }
        que.pop();
    }
    std::cout<<'\n';
    return;
}
#endif
