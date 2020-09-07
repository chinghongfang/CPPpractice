#include"tree.h"
#include"avl_tree.h"
using namespace std;
int main(){
    avl<int>* a_t = new avl<int>;
    a_t->insert(10);
    a_t->insert(2);
    a_t->insert(20);
    a_t->insert(15);
    a_t->insert(30);
    print_tree(a_t);
    a_t->insert(18);        // causing balance
    print_tree(a_t);
    a_t->del(10);
    a_t->del(2);
    print_tree(a_t);
    return 0;
}
